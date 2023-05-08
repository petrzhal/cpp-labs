#pragma once
#include <iostream>
#include <memory>
#include "iterator.h"
#include "node.h"

template <typename Key, typename Value>
class map {
    using pointer = std::shared_ptr<Node<Key, Value>>;
private:
    pointer root;
    size_t _size;
    void insert(pointer);
    void fix_insertion(pointer&);
    void left_rotate(pointer);
    void right_rotate(pointer);
    void fix_deletion(pointer&);
    void add_other(pointer);
    void clear(pointer&);

public:
    typedef iterator<Key, Value> iterator;

    map()
        : root(nullptr),
        _size(0) {}
    map(const map&);
    map& operator=(const map&);
    void insert(const Key&, const Value&);
    void erase(const Key&);
    Value& operator[](const Key&);
    iterator begin();
    iterator end();
    iterator find(const Key&);
    [[nodiscard]] size_t size() const;
    void clear();
    pointer& get_root() {
        return root;
    }
};

template<typename Key, typename Value>
void map<Key, Value>::insert(pointer node)
{
    ++_size;
    if (!root) {
        root = node;
        return;
    }
    auto cur = root;
    do {
        if (cur->data.first < node->data.first) {
            if (!cur->right) {
                node->parent = cur;
                cur->right = node;
                break;
            }
            else {
                cur = cur->right;
            }
        }
        else if (cur->data.first > node->data.first) {
            if (!cur->left) {
                node->parent = cur;
                cur->left = node;
                break;
            }
            else {
                cur = cur->left;
            }
        }
        else {
            _size--;
            return;
        }
    } while (true);
}

template<typename Key, typename Value>
void map<Key, Value>::fix_insertion(pointer& node)
{
    if (!node) {
        return;
    }
    if (!node->parent) {
        node->color = Color::Black;
        return;
    }

    auto parent = node->parent;
    if (parent->color == Color::Black) {
        return;
    }

    auto uncle = parent == parent->parent->left ? parent->parent->right : parent->parent->left;
    if (uncle && uncle->color == Color::Red) {
        parent->color = Color::Black;
        uncle->color = Color::Black;
        parent->parent->color = Color::Red;
        fix_insertion(parent->parent);
        return;
    }

    if (parent == parent->parent->left) {
        if (node == parent->right) {
            node = parent;
            left_rotate(node);
            parent = node->parent;
        }
        parent->color = Color::Black;
        if (parent->parent) {
            parent->parent->color = Color::Red;
            right_rotate(parent->parent);
        }
    }
    else {
        if (node == parent->left) {
            node = parent;
            right_rotate(node);
            parent = node->parent;
        }
        parent->color = Color::Black;
        if (parent->parent) {
            parent->parent->color = Color::Red;
            left_rotate(parent->parent);
        }
    }
}

template<typename Key, typename Value>
void map<Key, Value>::left_rotate(pointer node)
{
    if (!node->right)
        return;
    auto newRoot = node->right;
    if ((node->right = node->right->left)) {
        node->right->parent = node;
    }
    if (!node->parent) {
        root = newRoot;
    }
    else if (node == node->parent->left) {
        node->parent->left = newRoot;
    }
    else {
        node->parent->right = newRoot;
    }
    newRoot->parent = node->parent;
    node->parent = newRoot;
    newRoot->left = node;
}

template<typename Key, typename Value>
void map<Key, Value>::right_rotate(pointer node)
{
    if (!node->left)
        return;
    auto newRoot = node->left;
    if ((node->left = node->left->right)) {
        node->left->parent = node;
    }
    if (!node->parent) {
        root = newRoot;
    }
    else if (node == node->parent->left) {
        node->parent->left = newRoot;
    }
    else {
        node->parent->right = newRoot;
    }
    newRoot->parent = node->parent;
    node->parent = newRoot;
    newRoot->right = node;
}

template<typename Key, typename Value>
void map<Key, Value>::fix_deletion(pointer& node)
{
    if (!node) {
        return;
    }
    if (!node->parent) {
        node->color = Color::Black;
        return;
    }
    while (node->color == Color::Black && node) {
        if (node == node->parent->left) {
            auto brother = node->parent->right;
            if (brother->color == Color::Red) {
                brother->color = Color::Black;
                node->parent->color = Color::Red;
                left_rotate(node->parent);
                brother = node->parent->right;
            }

            if (brother->left->color == Color::Black && brother->right->color == Color::Black) {
                brother->color = Color::Red;
                node = node->parent;
            }
            else {
                if (brother->left->color == Color::Black) {
                    brother->right->color = Color::Black;
                    brother->color = Color::Red;
                    left_rotate(brother);
                    brother = node->parent->left;
                }
                brother->color = node->parent->color;
                node->parent->color = Color::Black;
                brother->left->color = Color::Black;
                right_rotate(node->parent);
                node = root;
            }
        }
    }
    node->color = Color::Black;
    root->color = Color::Black;
}

template<typename Key, typename Value>
void map<Key, Value>::add_other(pointer node)
{
    if (!node)
        return;
    add_other(node->left);
    insert(node->data.first, node->data.second);
    add_other(node->right);
}

template<typename Key, typename Value>
void map<Key, Value>::clear(pointer& node)
{
    if (!node) {
        return;
    }

    clear(node->left);
    clear(node->right);
    node.reset();
}

template<typename Key, typename Value>
void map<Key, Value>::erase(const Key& key)
{
    auto node = root;
    while (node) {
        if (key == node->data.first) {
            break;
        }
        else if (key < node->data.first) {
            node = node->left;
        }
        else {
            node = node->right;
        }
    }
    if (!node) {
        return;
    }
    if (node->left && node->right) {
        auto min_right = node->right;
        while (min_right->left) {
            min_right = min_right->left;
        }
        node->data.first = min_right->data.first;
        node->data.second = min_right->data.second;
        node = min_right;
    }
    auto child = node->left ? node->left : node->right;
    if (node == root) {
        root = child;
        if (root) {
            root->parent = nullptr;
        }
        node.reset();
        return;
    }

    if (node == node->parent->left) {
        node->parent->left = child;
    }
    else {
        node->parent->right = child;
    }
    if (child) {
        child->parent = node->parent;
    }

    if (node->color == Color::Black) {
        fix_deletion(child);
    }
    node.reset();
}

template<typename Key, typename Value>
Value& map<Key, Value>::operator[](const Key& key)
{
    auto cur = root;
    while (cur) {
        if (key < cur->data.first) {
            cur = cur->left;
        }
        else if (key > cur->data.first) {
            cur = cur->right;
        }
        else {
            return cur->data.second;
        }
    }
    insert(key, Value());
    return (*this)[key];
}

template<typename Key, typename Value>
typename map<Key, Value>::iterator map<Key, Value>::begin()
{
    auto tmp = root;
    while (tmp->left) {
        tmp = tmp->left;
    }
    return iterator(tmp, root);
}

template<typename Key, typename Value>
typename map<Key, Value>::iterator map<Key, Value>::end()
{
    return iterator(nullptr, root);
}

template<typename Key, typename Value>
iterator<Key, Value> map<Key, Value>::find(const Key& key)
{
    auto cur = root;
    while (cur) {
        if (key < cur->data.first) {
            cur = cur->left;
        }
        else if (key > cur->data.first) {
            cur = cur->right;
        }
        else {
            return { cur, root };
        }
    }
    return { nullptr, root };
}

template<typename Key, typename Value>
size_t map<Key, Value>::size() const
{
    return _size;
}

template<typename Key, typename Value>
void map<Key, Value>::clear()
{
    clear(root);
    _size = 0;
}

template<typename Key, typename Value>
map<Key, Value>::map(const map& other)
{
    root = nullptr;
    _size = 0;
    add_other(other.root);
}

template<typename Key, typename Value>
map<Key, Value>& map<Key, Value>::operator=(const map& other)
{
    if (this != &other) {
        clear();
        root = nullptr;
        _size = 0;
        add_other(other.root);
    }
    return *this;
}

template<typename Key, typename Value>
void map<Key, Value>::insert(const Key& key, const Value& value)
{
    auto node = std::make_shared<Node<Key, Value>>(key, value, nullptr);
    insert(node);
    auto tmp = node;
    fix_insertion(tmp);
}
