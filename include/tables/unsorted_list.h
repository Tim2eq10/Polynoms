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



template <typename kT, typename T>
typename _Table_unsorted_list<kT, T>::Node* _Table_unsorted_list<kT, T>::__Find(key_cref key) const {
    Node* node = head;
    for (; node; node = node->next) {
        if (node->key == key)
            break;
    }
    return node;
}

template <typename kT, typename T>
bool _Table_unsorted_list<kT, T>::insert(key_cref key, cref value, bool replacement) {
    Node* place = __Find(key);
    if (place == nullptr) {
        place = new Node(key, value);
        place->next = head;
        head = place;
        sz++;
        return 1;
    }
    if (replacement)
        place->value = value;
    return 0;
}

template <typename kT, typename T>
bool _Table_unsorted_list<kT, T>::remove(key_cref key) {
    if (head == nullptr)
        return 0;
    if (head->key == key) {
        delete head;
        head = nullptr;
        sz--;
        return 1;
    }
    Node* node = head;
    for (; node->next && node->next->key != key; node = node->next);
    if (node->next == nullptr)
        return 0;
    Node* tmp = node->next;
    node->next = node->next->next;
    delete tmp;
    sz--;
    return 1;
}

template <typename kT, typename T>
ND bool _Table_unsorted_list<kT, T>::find(key_cref key) {
    return __Find(key) != nullptr;
}

template <typename kT, typename T>
ND typename _Table_unsorted_list<kT, T>::ref _Table_unsorted_list<kT, T>::at(key_cref key) {
    Node* place = __Find(key);
    if (place == nullptr)
        throw std::invalid_argument("No key in table");
    return place->value;
}

#endif // UNSORTED_LIST_H
