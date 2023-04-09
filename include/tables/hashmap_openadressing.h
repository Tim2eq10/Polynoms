#include "include/tables/hasher.h"

#ifndef HASHMAP_OPENADRESSING_H
#define HASHMAP_OPENADRESSING_H

#define ND [[nodiscard]]

template <
    typename kT,
    typename T,
    typename hasher = _Hasher<kT>
>
class _HashMap_OpenAddressing {
    using key_type = kT;
    using key_cref = const kT&;
    using value_type = T;
    using ref = T&;
    using cref = const T&;
    using size_type = size_t;

    class Node {
    public:
        bool keep_finding;
        bool has_value;
        key_type key;
        value_type value;

        Node() = delete;
    };

    const static double MAX_LOAD_FACTOR_THRESHOLD; //definition outside
    const static size_t MAX_ARRAY_SIZE_THRESHOLD = 100000;
    const static size_t k = 1;
private:
    ND size_t __hash(key_cref key, size_t cap) noexcept {
        return hasher::hash(key) % cap;
    }
    ND size_t hash(key_cref key) noexcept {
        return __hash(key, cap);
    }
    ND size_t __hash_next_it(size_t _hash, size_t cap) noexcept {
        return (_hash + k) % cap;
    }
    ND size_t hash_next_it(size_t _hash) noexcept {
        return __hash_next_it(_hash, cap);
    }

    ND double load_factor() noexcept {
        return static_cast<double>(added) / cap;
    }
    ND bool load_factor_too_big() noexcept {
        return load_factor() > MAX_LOAD_FACTOR_THRESHOLD;
    }

    ND bool __keep_finding(Node* mem, size_t index) noexcept {
        return *(reinterpret_cast<bool*>(mem + index));
    }
    ND bool keep_finding(size_t index) noexcept {
        return __keep_finding(mem, index);
    }
    ND bool __has_value(Node* mem, size_t index) noexcept {
        return *(reinterpret_cast<bool*>(mem + index) + sizeof(Node::keep_finding));
    }
    ND bool has_value(size_t index) noexcept {
        return __has_value(mem, index);
    }
    key_type* __key_place(Node* mem, size_t index) noexcept {
        return
            reinterpret_cast<key_type*>(
                reinterpret_cast<uint8_t*>(mem + index)
                + sizeof(Node::keep_finding)
                + sizeof(Node::has_value)
                );
    }
    key_type* key_place(size_t index) noexcept {
        return __key_place(mem, index);
    }
    value_type* __value_place(Node* mem, size_t index) noexcept {
        return
            reinterpret_cast<value_type*>(
                reinterpret_cast<uint8_t*>(mem + index)
                + sizeof(Node::keep_finding)
                + sizeof(Node::has_value)
                + sizeof(key_type)
                );
    }
    value_type* value_place(size_t index) noexcept {
        return __value_place(mem, index);
    }

    void rehash(size_type _capacity, Node* new_mem, size_t& added);
    void reserve(size_type _new_capacity);

    ND Node* __Find(key_cref key);
    ND Node* __Find_Insert(key_cref key) noexcept;
public:
    _HashMap_OpenAddressing() : mem(nullptr) {
        sz = 0;
        cap = 0;
        added = 0;
        reserve(8);
    }
    ND size_type size() const noexcept { return sz; }
    ND bool empty() const noexcept { return sz == 0; }
    ND size_type capacity() const noexcept { return cap; }

    /// <summary>
    /// Insert an element {key, value} to table
    /// Does not break the order
    /// <para>If (the item is in the table AND replacement == false) do nothing</para>
    /// <para>If (the item is in the table AND replacement == true) assign value</para>
    /// <para>Asymptotic O(1)</para>
    /// </summary>
    /// <returns>1 -> inserted, 0 -> assigned (or not assigned if !replacement)</returns>
    bool insert(key_cref key, cref value, bool replacement = false);

    /// <summary>
    /// Removes an element {key, value} from table
    /// <para>Asymptotic O(1)</para>
    /// </summary>
    /// <returns>1 -> removed, 0 -> not found</returns>
    bool remove(key_cref key);

    /// <summary>
    /// <para>Asymptotic O(1)</para>
    /// </summary>
    /// <returns>Return true if the element is found in the table</returns>
    ND bool find(key_cref key);
    ND ref at(key_cref key);
private:
    Node* mem;
    size_t sz;
    size_t cap;

    size_t added;
};
template <typename kT, typename T, typename hasher>
const double _HashMap_OpenAddressing<kT, T, hasher>::MAX_LOAD_FACTOR_THRESHOLD = 0.75;

template <typename kT, typename T, typename hasher>
void _HashMap_OpenAddressing<kT, T, hasher>::rehash(size_type _capacity, Node* new_mem, size_t& added) {
    size_t h;
    bool key_created{};
    try {
        for (size_t i = 0; i < cap; i++)
            if (has_value(i)) {
                key_created = 0;

                h = __hash(*key_place(i), _capacity);
                while (__keep_finding(new_mem, h)) {
                    h = __hash_next_it(h, _capacity);
                }

                new (__key_place(new_mem, h)) key_type(*key_place(i));
                key_created = 1;
                new (__value_place(new_mem, h)) value_type(*value_place(i));

                new_mem[h].keep_finding = 1;
                new_mem[h].has_value = 1;
                added++;
            }
    }
    catch (std::exception _ex) {
        for (size_t i = 0; i < _capacity; i++)
            if (i == h) {
                if(key_created)
                    __key_place(new_mem, i)->~key_type();
            }
            else if (__has_value(new_mem, i)) {
                (__key_place(new_mem, i))->~key_type();
                (__value_place(new_mem, i))->~value_type();
            }
        throw _ex;
    }
}

template <typename kT, typename T, typename hasher>
void _HashMap_OpenAddressing<kT, T, hasher>::reserve(size_type _new_capacity) {
    if (_new_capacity <= cap)
        return;

    Node* new_mem =
        reinterpret_cast<Node*>(new uint8_t[_new_capacity * sizeof(Node)]());

    size_t number_of_added{};
    try {
        rehash(_new_capacity, new_mem, number_of_added);
    }
    catch (std::exception _ex) {
        delete[]
            reinterpret_cast<uint8_t*>(new_mem);
        throw _ex;
    }

    //delete[] mem;
    for (size_t i = 0; i < cap; i++) {
        if (has_value(i)) {
            key_place(i)->~key_type();
            value_place(i)->~value_type();
        }
    }
    delete[]
        reinterpret_cast<uint8_t*>(mem);

    mem = new_mem;
    cap = _new_capacity;
    added = number_of_added;
}

template <typename kT, typename T, typename hasher>
ND typename _HashMap_OpenAddressing<kT, T, hasher>::Node*
    _HashMap_OpenAddressing<kT, T, hasher>::__Find(key_cref key)
{
    size_t h = hash(key);
    while (keep_finding(h)) {
        if (has_value(h)) {
            if (*key_place(h) == key)
                return mem + h;
        }
        h = hash_next_it(h);
    }
    return mem + h;
}

template <typename kT, typename T, typename hasher>
ND typename _HashMap_OpenAddressing<kT, T, hasher>::Node*
    _HashMap_OpenAddressing<kT, T, hasher>::__Find_Insert(key_cref key) noexcept
{
    size_t h = hash(key);
    while (has_value(h)) {
        h = hash_next_it(h);
    }
    return mem + h;
}

template <typename kT, typename T, typename hasher>
bool _HashMap_OpenAddressing<kT, T, hasher>::insert(
    key_cref key,
    cref value,
    bool replacement
) {
    if (load_factor_too_big())
            reserve(2 * cap);
    auto place = __Find_Insert(key);
    if (!__has_value(place, 0)) {
        new (__key_place(place, 0)) key_type(key);
        try {
            new (__value_place(place, 0)) value_type(value);
        }
        catch (std::exception _ex) {
            (__key_place(place, 0))->~key_type();
            throw _ex;
        }

        place->keep_finding = 1;
        place->has_value = 1;

        sz++;
        added++;
        return 1;
    }
    if (replacement) {
        *__key_place(place, 0) = key;
        *__value_place(place, 0) = value;
    }
    return 0;
}

template <typename kT, typename T, typename hasher>
bool _HashMap_OpenAddressing<kT, T, hasher>::remove(key_cref key) {
    auto place = __Find(key);
    if (!__has_value(place, 0)) {
        return 0;
    }
    __key_place(place, 0)->~key_type();
    __value_place(place, 0)->~value_type();
    place->has_value = 0;
    sz--;
    return 1;
}

template <typename kT, typename T, typename hasher>
ND bool _HashMap_OpenAddressing<kT, T, hasher>::find(key_cref key) {
    return __has_value(__Find(key), 0);
}

template <typename kT, typename T, typename hasher>
ND typename _HashMap_OpenAddressing<kT, T, hasher>::ref
    _HashMap_OpenAddressing<kT, T, hasher>::at(key_cref key)
{
    auto place = __Find(key);
    if (!__has_value(place, 0))
        throw std::invalid_argument("key isn't found");
    return *__value_place(place, 0);
}

#endif // HASHMAP_OPENADRESSING_H
