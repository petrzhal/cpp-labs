#pragma once
#include <iostream>
#include <memory>
#include "node.h"

template <typename Key, typename Value>
class iterator {
    using pointer    = std::shared_ptr<Node<Key, Value>>;
    using value_type = std::pair<Key, Value>;
private:
    pointer cur;
    pointer root;

public:
    iterator(const pointer& ptr, const pointer& root)
        : cur(ptr),
        root(root) {}

    iterator& operator++() {
        if (!cur) {
            return *this;
        }

        if (cur->right) {
            cur = cur->right;
            while (cur->left) {
                cur = cur->left;
            }
        }
        else {
            auto parent = cur->parent;
            while (parent && cur == parent->right) {
                cur = parent;
                parent = parent->parent;
            }
            cur = parent;
        }
        return *this;
    }

    iterator& operator--() {
        if (!cur) {
            if (!root)
                return *this;
            cur = root;
            while (cur->right) {
                cur = cur->right;
            }
            return *this;
        }

        if (cur->left) {
            cur = cur->left;
            while (cur->right) {
                cur = cur->right;
            }
        }
        else {
            auto parent = cur->parent;
            while (parent && cur == parent->left) {
                cur = parent;
                parent = parent->parent;
            }
            cur = parent;
        }
        return *this;
    }

    value_type& operator*() {
        return cur->data;
    }

    bool operator==(const iterator& other) {
        return cur == other.cur;
    }

    bool operator!=(const iterator& other) {
        return cur != other.cur;
    }
};