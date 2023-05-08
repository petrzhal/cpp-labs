#pragma once
#include <iostream>
#include <memory>

enum Color {
    Red,
    Black
};

template <typename Key, typename Value>
struct Node {
    std::pair<Key, Value> data;
    Color color;
    std::shared_ptr<Node<Key, Value>> left;
    std::shared_ptr<Node<Key, Value>> right;
    std::shared_ptr<Node<Key, Value>> parent;
    Node()
        : data(Key(), Value()),
        color(Color::Red),
        parent(nullptr),
        left(nullptr),
        right(nullptr) {}
    Node(const Key& key, const Value& value, std::shared_ptr<Node<Key, Value>> parent)
        : data(key, value),
        color(Color::Red),
        parent(parent),
        left(nullptr),
        right(nullptr) {}
};