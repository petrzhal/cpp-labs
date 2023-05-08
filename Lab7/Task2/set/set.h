#pragma once
#include <iostream>
#include <memory>
#include "iterator.h"
#include "node.h"

template <typename Key>
class set {
    using pointer = std::shared_ptr<Node<Key>>;
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
    typename typedef iterator<Key> iterator;

    set()
        : root(nullptr),
        _size(0) {}
    set(const set&);
    set& operator=(const set&);
    void insert(const Key&);
    void erase(const Key&);
    iterator begin();
    iterator end();
    iterator find(const Key&);
    void clear();
    pointer& get_root() {
        return root;
    }
};

template<typename Key>
typename iterator<Key> set<Key>::find(const Key& key)
{
    auto cur = root;
    while (cur) {
        if (key < cur->key) {
            cur = cur->left;
        }
        else if (key > cur->key) {
            cur = cur->right;
        }
        else {
            return { cur, root };
        }
    }
    return { nullptr, root };
}

template<typename Key>
void set<Key>::insert(pointer node)
{
    ++_size;
    if (!root) {
        root = node;
        return;
    }
    auto cur = root;
    do {
        if (cur->key < node->key) {
            if (!cur->right) {
                node->parent = cur;
                cur->right = node;
                break;
            }
            else {
                cur = cur->right;
            }
        }
        else if (cur->key >= node->key) {
            if (!cur->left) {
                node->parent = cur;
                cur->left = node;
                break;
            }
            else {
                cur = cur->left;
            }
        }
    } while (true);
}

template<typename Key>
void set<Key>::fix_insertion(pointer& node)
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

template<typename Key>
void set<Key>::left_rotate(pointer node)
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

template<typename Key>
void set<Key>::right_rotate(pointer node)
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

template<typename Key>
void set<Key>::fix_deletion(pointer& node)
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

template<typename Key>
void set<Key>::add_other(pointer node)
{
    if (!node)
        return;
    add_other(node->left);
    insert(node->key);
    add_other(node->right);
}

template<typename Key>
void set<Key>::clear(pointer& node)
{
    if (!node) {
        return;
    }

    clear(node->left);
    clear(node->right);
    node.reset();
}

template<typename Key>
void set<Key>::erase(const Key& key)
{
    auto node = root;
    while (node) {
        if (key == node->key) {
            break;
        }
        else if (key < node->key) {
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
        node->key = min_right->key;
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

template<typename Key>
void set<Key>::clear()
{
    clear(root);
    _size = 0;
}

template<typename Key>
set<Key>::set(const set& other)
{
    root = nullptr;
    _size = 0;
    add_other(other.root);
}

template<typename Key>
set<Key>& set<Key>::operator=(const set& other)
{
    if (this != &other) {
        clear();
        root = nullptr;
        _size = 0;
        add_other(other.root);
    }
    return *this;
}

template<typename Key>
typename set<Key>::iterator set<Key>::begin()
{
    auto tmp = root;
    while (tmp->left) {
        tmp = tmp->left;
    }
    return iterator(tmp, root);
}

template<typename Key>
typename set<Key>::iterator set<Key>::end()
{
    return iterator(nullptr, root);
}

template<typename Key>
void set<Key>::insert(const Key& key)
{
    auto node = std::make_shared<Node<Key>>(key, nullptr);
    insert(node);
    auto tmp = node;
    fix_insertion(tmp);
}
