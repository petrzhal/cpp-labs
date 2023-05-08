#pragma once
#include <iostream>
#include <memory>

enum Color {
    Red,
    Black
};

template <typename Key>
struct Node {
    using pointer = std::shared_ptr<Node<Key>>;

    Key key;
    Color color;
    pointer left;
    pointer right;
    pointer parent;
    Node()
        : key(Key()),
        color(Color::Red),
        parent(nullptr),
        left(nullptr),
        right(nullptr) {}
    Node(const Key& key, pointer parent)
        : key(key),
        color(Color::Red),
        parent(parent),
        left(nullptr),
        right(nullptr) {}
};