
#include <memory>

#ifndef UNSORTED_ARRAY_H
#define UNSORTED_ARRAY_H

#define ND [[nodiscard]]

/// <summary>
/// Associative container that contains key-value pairs with unique keys.
/// </summary>
/// <typeparam name="kT">Key type</typeparam>
/// <typeparam name="T">Value type</typeparam>
template <typename kT, typename T>
class _Table_unsorted_array {
    using key_type = kT;
    using key_cref = const kT&;
    using value_type = T;
    using ref = T&;
    using cref = const T&;
    using size_type = size_t;

    struct Node {
        key_type key;
        value_type value;
        Node(key_cref _key, cref _value)
            : key(_key),
            value(_value) {
        }
    };
private:
    void reserve(size_type _new_capacity);
    Node* __Find(key_cref key) const;

public:

    _Table_unsorted_array()
        : sz(0), cap(0), mem(nullptr) {
        reserve(1);
    }

    ND size_type size() const noexcept { return sz; }
    ND bool empty() const noexcept { return sz == 0; }
    ND size_type capacity() const noexcept { return cap; }
    void shrink_to_fit();

    /// <summary>
    /// Insert an element {key, value} to table
    /// <para>If (the item is in the table AND replacement == false) do nothing</para>
    /// <para>If (the item is in the table AND replacement == true) assign value</para>
    /// <para>Asymptotic Amortized constant</para>
    /// </summary>
    /// <returns>1 -> inserted, 0 -> assigned (or not assigned if !replacement)</returns>
    bool insert(key_cref key, cref value, bool replacement = false);

    /// <summary>
    /// Removes an element {key, value} from table
    /// <para>Asymptotic O(n)</para>
    /// </summary>
    /// <returns>1 -> removed, 0 -> not found</returns>
    bool remove(key_cref key);

    /// <summary>
    /// <para>Asymptotic O(n)</para>
    /// </summary>
    /// <returns>Return true if the element is found in the table</returns>
    ND bool find(key_cref key);

    ND ref at(key_cref key);

private:
    Node* mem;
    size_type sz;
    size_type cap;
};



template<typename kT, typename T>
void _Table_unsorted_array<kT, T>::reserve(size_type _new_capacity){
    if (_new_capacity <= cap) return;

    Node* new_mem =
        reinterpret_cast<Node*>(new uint8_t[_new_capacity * sizeof(Node)]);

    try {
        std::uninitialized_copy(mem, mem + sz, new_mem);
    }
    catch (...) {
        delete[] reinterpret_cast<uint8_t*>(new_mem);
        throw;
    }

    for (size_t i = 0; i < sz; i++)
        (mem + i)->~Node();
    delete[] reinterpret_cast<uint8_t*>(mem);
    mem = new_mem;
    cap = _new_capacity;
}

template<typename kT, typename T>
typename _Table_unsorted_array<kT, T>::Node*
    _Table_unsorted_array<kT, T>::__Find(key_cref key) const
{
    Node* it = mem;
    for (; it < mem + sz; it++) {
        if (it->key == key)
            break;
    }
    return it;
}

template <typename kT, typename T>
void _Table_unsorted_array<kT, T>::shrink_to_fit() {
    value_type* new_mem =
        reinterpret_cast<Node*>(new uint8_t[sz * sizeof(Node)]);

    try {
        std::uninitialized_copy(mem, mem + sz, new_mem);
    }
    catch (...) {
        delete[] reinterpret_cast<uint8_t*>(new_mem);
        throw;
    }

    for (size_t i = 0; i < sz; i++)
        (mem + i)->~Node();
    delete[] reinterpret_cast<uint8_t*>(mem);
    mem = new_mem;
    cap = sz;
}

template<typename kT, typename T>
bool _Table_unsorted_array<kT, T>::insert(key_cref key, cref value, bool replacement)
{
    if (sz == cap)
        //TODO : "2 * sz" is some function
        reserve(2 * sz);
    Node* place = __Find(key);
    if (place == mem + sz) {
        new (mem + sz) Node(key, value);
        sz++;
        return 1;
    }
    if (replacement)
        place->value = value;
    return 0;
}

template <typename kT, typename T>
bool _Table_unsorted_array<kT, T>::remove(key_cref key) {
    Node* place = __Find(key);
    if (place == mem + sz)
        return 0;

    for (; place < mem + sz; place++) {
        place->~Node();
        new (place) Node(std::move(*(place + 1)));
    }
    place->~Node();
    sz--;
    return 1;
}

template <typename kT, typename T>
ND bool _Table_unsorted_array<kT, T>::find(key_cref key) {
    return __Find(key) != mem + sz;
}

template <typename kT, typename T>
ND typename _Table_unsorted_array<kT, T>::ref _Table_unsorted_array<kT, T>::at(key_cref key) {
    Node* place = __Find(key);
    if (place == mem + sz)
        throw std::invalid_argument("No key in table");
    return place->value;
}

#endif // UNSORTED_ARRAY_H
