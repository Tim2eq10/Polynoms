#include <list>

#include "include/tables/hasher.h"

#ifndef HASHMAP_CHAINS_H
#define HASHMAP_CHAINS_H

#define ND [[nodiscard]]

/// <summary>
/// Associative container that contains key-value pairs with unique keys.
/// Hash-table.
/// </summary>
/// <typeparam name="kT">Key type</typeparam>
/// <typeparam name="T">Value type</typeparam>
/// <typeparam name="hasher">Struct hasher which has static function ::hash(T)</typeparam>
template <
    typename kT,
    typename T,
    typename hasher = _Hasher<kT>
>
class _HashMap_Chains {
    using key_type = kT;
    using key_cref = const kT&;
    using value_type = T;
    using ref = T&;
    using cref = const T&;
    using size_type = size_t;

    struct ListNode {
        kT key;
        T value;
        ListNode(key_cref key, cref value)
            : key(key), value(value) {
        }
    };
    using Node = std::list<ListNode>;

    const static size_t MAX_LIST_LEN_THRESHOLD = 3;
    const static size_t MAX_ARRAY_SIZE_THRESHOLD = 100000;
private:
    ND size_t hash(const kT& key) noexcept {
        return hasher::hash(key) % cap;
    }

    void rehash(size_type _new_capacity, Node* new_mem, size_t& max_list_len);
    void reserve(size_type _new_capacity);
    ND auto __Find(key_type key);
public:
    _HashMap_Chains() :
        sz(0), cap(0), max_list_len(0), mem(nullptr) {
        reserve(1);
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

    size_t max_list_len;
};



template <typename kT, typename T, typename hasher>
void _HashMap_Chains<kT, T, hasher>::rehash(
    size_type _new_capacity,
    Node* new_mem,
    size_t& max_list_len
) {
    for (size_t hs = 0; hs < cap; hs++)
        for (ListNode& el : mem[hs]) {
            auto& new_lst = new_mem[hasher::hash(el.key) % _new_capacity];
            new_lst.insert(new_lst.begin(), el);

            if (new_lst.size() > max_list_len) {
                max_list_len = new_lst.size();
            }

        }
}

template <typename kT, typename T, typename hasher>
void _HashMap_Chains<kT, T, hasher>::reserve(size_type _new_capacity)
{
   if (_new_capacity <= cap) return;

   Node* new_mem = new Node[_new_capacity];

   size_t len = 0;

   try {
       rehash(_new_capacity, new_mem, len);
   }
   catch (std::exception _ex) {
       delete[] new_mem;
       throw _ex;
   }

   delete[] mem;
   max_list_len = len;
   mem = new_mem;
   cap = _new_capacity;
}

template <typename kT, typename T, typename hasher>
ND auto _HashMap_Chains<kT, T, hasher>::__Find(key_type key) {
    auto it = mem[hash(key)].begin();
    auto end = mem[hash(key)].end();
    for (; it != end; it++)
        if (it->key == key)
            return it;
    return it;
}

template <typename kT, typename T, typename hasher>
bool _HashMap_Chains<kT, T, hasher>::insert(
    key_cref key,
    cref value,
    bool replacement
) {
    if (max_list_len > MAX_LIST_LEN_THRESHOLD) {
        if (2 * cap > MAX_ARRAY_SIZE_THRESHOLD) {
            reserve(MAX_ARRAY_SIZE_THRESHOLD);
        }
        else {
            reserve(2 * cap);
        }
    }
    auto place = __Find(key);
    size_t hs = hash(key);
    if (place == mem[hs].end()) {
        mem[hs].insert(place, ListNode(key, value));
        sz++;
        max_list_len = (mem[hs].size() > max_list_len ? mem[hs].size() : max_list_len);
        return 1;
    }
    if (replacement) {
        place->value = value;
    }
    return 0;
}

template <typename kT, typename T, typename hasher>
bool _HashMap_Chains<kT, T, hasher>::remove(key_cref key) {
    auto place = __Find(key);
    if (place == mem[hash(key)].end())
        return 0;

    mem[hash(key)].erase(place);
    sz--;
    return 1;
}

template <typename kT, typename T, typename hasher>
ND bool _HashMap_Chains<kT, T, hasher>::find(key_cref key) {
    return __Find(key) != mem[hash(key)].end();
}

template <typename kT, typename T, typename hasher>
ND typename _HashMap_Chains<kT, T, hasher>::ref
    _HashMap_Chains<kT, T, hasher>::at(key_cref key)
{
    auto place = __Find(key);
    if (place == mem[hash(key)].end())
        throw std::invalid_argument("No key in table");
    return place->value;
}

#endif // HASHMAP_CHAINS_H
