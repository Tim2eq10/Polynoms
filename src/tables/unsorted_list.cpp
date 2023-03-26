#include "include/tables/unsorted_list.h"

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
