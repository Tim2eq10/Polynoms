#include <memory>

#ifndef SORTED_ARRAY_H
#define SORTED_ARRAY_H

#define ND [[nodiscard]]

/// <summary>
/// Associative container that contains key-value pairs with unique keys.
/// </summary>
/// <typeparam name="kT">Key type</typeparam>
/// <typeparam name="T">Value type</typeparam>
template <typename kT, typename T>
class _Table_sorted_array {
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
    Node* __Lower_bound(key_cref key) const;
public:

    _Table_sorted_array()
        : sz(0), cap(0) {
        reserve(1);
    }

    ND size_type size() const noexcept { return sz; }
    ND bool empty() const noexcept { return sz == 0; }
    ND size_type capacity() const noexcept { return cap; }
    void shrink_to_fit();

    /// <summary>
    /// Insert an element {key, value} to table
    /// Does not break the order
    /// <para>If (the item is in the table AND replacement == false) do nothing</para>
    /// <para>If (the item is in the table AND replacement == true) assign value</para>
    /// <para>Asymptotic O(n)</para>
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
    /// <para>Asymptotic O(log(n))</para>
    /// </summary>
    /// <returns>Return true if the element is found in the table</returns>
    ND bool find(key_cref key);

    ND ref at(key_cref key);

private:
    Node* mem;
    size_type sz;
    size_type cap;
};

#endif // SORTED_ARRAY_H
