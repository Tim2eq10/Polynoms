#include <algorithm>
#include <stdexcept>

#ifndef TREE_AVL_H
#define TREE_AVL_H

#define ND [[nodiscard]]

/// <summary>
/// Associative container that contains key-value pairs with unique keys.
/// <para> Binary search tree. </para>
/// </summary>
/// <typeparam name="kT">Key type</typeparam>
/// <typeparam name="T">Value type</typeparam>
template <typename kT, typename T>
class _Map_AVL_Tree {
    using key_type = kT;
    using key_cref = const kT&;
    using value_type = T;
    using ref = T&;
    using cref = const T&;
    using size_type = size_t;

    struct Node {
        key_type key;
        value_type value;
        unsigned char height;
        Node* left;
        Node* right;
        Node(
            key_cref _key,
            cref _value
        )
            : key(_key),
            value(_value),
            height(1),
            left(nullptr),
            right(nullptr) {
        }
    };
private:
    unsigned char height(Node* node) {
        return (node != nullptr ? node->height : 0);
    }
    char balance_factor(Node* node) {
        return
            static_cast<char>(height(node->right))
            -
            static_cast<char>(height(node->left));
    }
    void fix_height(Node* node) {
        node->height = std::max(height(node->left), height(node->right)) + 1;
    }

    Node* _RotateLeft(Node* node) {
        Node* new_node = node->right;
        node->right = new_node->left;
        new_node->left = node;
        fix_height(node);
        fix_height(new_node);
        return new_node;
    }
    Node* _RotateRight(Node* node) {
        Node* new_node = node->left;
        node->left = new_node->right;
        new_node->right = node;
        fix_height(node);
        fix_height(new_node);
        return new_node;
    }
    Node* balance(Node* node) {
        fix_height(node);
        if (balance_factor(node) == 2) {
            if (balance_factor(node->right) < 0)
                node->right = _RotateRight(node->right);
            node = _RotateLeft(node);
        }
        if (balance_factor(node) == -2) {
            if (balance_factor(node->left) > 0)
                node->left = _RotateLeft(node->left);
            node = _RotateRight(node);
        }
        return node;
    }

    Node* findmin(Node* node) {
        return node->left ? findmin(node->left) : node;
    }
    Node* removemin(Node* node) {
        if (node->left == nullptr)
            return node->right;
        node->left = removemin(node->left);
        return balance(node);
    }

    Node* __Insert(Node* node, key_cref key, cref value, bool replacement) {
        if (node == nullptr) {
            sz++;
            return new Node(key, value);
        }
        if (key < node->key)
            node->left = __Insert(node->left, key, value, replacement);
        else if (key > node->key)
            node->right = __Insert(node->right, key, value, replacement);
        else if (replacement) {
            node->value = value;
        }

        return balance(node);
    }
    Node* __Remove(Node* node, key_cref key)
    {
        if (node == nullptr)
            return nullptr;
        if (key < node->key)
            node->left = __Remove(node->left, key);
        else if (key > node->key)
            node->right = __Remove(node->right, key);
        else //  key == node->key
        {
            Node* left_node = node->left;
            Node* right_node = node->right;
            delete node;
            sz--;
            if (right_node == nullptr)
                return left_node;
            Node* min = findmin(right_node);
            min->right = removemin(right_node);
            min->left = left_node;
            return balance(min);
        }
        return balance(node);
    }
    Node* __Find(Node* node, key_cref key) {
        if (node == nullptr)
            return nullptr;

        if (key < node->key)
            return __Find(node->left, key);
        if (key > node->key)
            return __Find(node->right, key);

        return node;
    }
public:
    _Map_AVL_Tree()
        : root(nullptr),
        sz(0) {
    }

    ND size_type size() const noexcept {
        return sz;
    }
    ND bool empty() const noexcept {
        return sz == 0;
    }

    /// <summary>
    /// Insert an element {key, value} to tree
    /// <para>If (the item is in the table AND replacement == false) do nothing</para>
    /// <para>If (the item is in the table AND replacement == true) assign value</para>
    /// <para>Asymptotic O(log(n))</para>
    /// </summary>
    /// <returns>1 -> inserted, 0 -> assigned(or not assigned if !replacement)</returns>
    void insert(key_cref key, cref value, bool replacement = false) {
        root = __Insert(root, key, value, replacement);
    }

    /// <summary>
    /// Removes an element {key, value} from tree
    /// <para>Asymptotic O(log(n))</para>
    /// </summary>
    /// <returns>1 -> removed, 0 -> not found</returns>
    void remove(key_cref key) {
        root = __Remove(root, key);
    }

    /// <summary>
    /// <para>Asymptotic O(log(n))</para>
    /// </summary>
    /// <returns>Return true if the element is found in the tree</returns>
    ND bool find(key_cref key) {
        return __Find(root, key) != nullptr;
    }
    ND ref at(key_cref key) {
        Node* place = __Find(root, key);
        if (place == nullptr)
            throw std::invalid_argument("No key in table");
        return place->value;
    }
public:
    Node* root;
    size_type sz;
};

#endif // TREE_AVL_H
