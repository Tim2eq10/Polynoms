#include <stdexcept>

#ifndef UNSORTED_LIST_H
#define UNSORTED_LIST_H

#define ND [[nodiscard]]

/// <summary>
/// Associative container that contains key-value pairs with unique keys.
/// </summary>
/// <typeparam name="kT">Key type</typeparam>
/// <typeparam name="T">Value type</typeparam>
template <typename kT, typename T>
class _Table_unsorted_list {
    using key_type = kT;
    using key_cref = const kT&;
    using value_type = T;
    using ref = T&;
    using cref = const T&;
    using size_type = size_t;

    struct Node {
        key_type key;
        value_type value;
        Node* next;
        Node(key_cref _key, cref _value, Node* _next = nullptr)
            : key(_key),
            value(_value),
            next(_next) {
        }
    };
private:
    Node* __Find(key_cref key) const;
public:
    _Table_unsorted_list()
        : sz(0),
        head(nullptr) {
    }

    ND size_type size() const noexcept { return sz; }
    ND bool empty() const noexcept { return sz == 0; }

    /// <summary>
    /// Insert an element {key, value} to table
    /// <para>If (the item is in the table AND replacement == false) do nothing</para>
    /// <para>If (the item is in the table AND replacement == true) assign value</para>
    /// <para>Asymptotic O(1)</para>
    /// </summary>
    /// <returns>1 -> inserted, 0 -> assigned(or not assigned if !replacement)</returns>
    bool insert(key_cref key, cref value, bool replacement = false);

    /// <summary>
    /// Removes an element {key, value} from table
    /// <para>Asymptotic O(1)</para>
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
    Node* head;
    size_t sz;
};

#endif // UNSORTED_LIST_H
