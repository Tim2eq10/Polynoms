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
        sz(0), cap(0), max_list_len(0) {
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

#endif // HASHMAP_CHAINS_H
