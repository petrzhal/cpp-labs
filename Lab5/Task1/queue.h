#ifndef QUEUE_QUEUE_H
#define QUEUE_QUEUE_H

//#include "shared.h"
#include <iostream>
#include <memory>

using std::shared_ptr;

template<typename T>
class queue {
private:
    struct Node {
        std::shared_ptr<Node> next;
        std::weak_ptr<Node> prev;
        T data;
        explicit Node(const T &value) : data(value), next(nullptr), prev(next) {}
        Node() : next(nullptr), prev(next), data(T()) {}
        ~Node() = default;
    };
    shared_ptr<Node> _begin;
    shared_ptr<Node> _end;
    size_t _size;

public:
    queue() : _size(0) {
        _begin = std::make_shared<Node>();
        _end = _begin;
    }
    queue(const queue &);
    queue(queue &&) noexcept;
    queue &operator=(const queue &);
    queue &operator=(queue &&) noexcept;
    [[nodiscard]] size_t size() const;
    void push(const T &);
    void pop();
    T &back();
    T &front();
    bool empty();
    void swap(queue &);
    void clear();
    template<typename... Args>
    void emplace(Args &&...);
};

template<typename T>
template<typename... Args>
void queue<T>::emplace(Args &&...args) {
    queue::push(T(args...));
}

template<typename T>
queue<T> &queue<T>::operator=(queue &&other) noexcept {
    clear();
    _begin = other._begin;
    _end = other._end;
    _size = other._size;
    other._begin.reset();
    other._end.reset();
    other._size = 0;
    return *this;
}

template<typename T>
void queue<T>::clear() {
    if (_size) {
        _begin.reset();
        _end.reset();
        _begin = std::make_shared<Node>();
        _end = _begin;
        _size = 0;
    }
}

template<typename T>
queue<T> &queue<T>::operator=(const queue &other) {
    clear();
    _size = 0;
    _begin = std::make_shared<Node>(Node());
    _end = _begin;
    auto it(other._begin);
    for (size_t i = 0; i < other._size; ++i) {
        queue::push(it->data);
        it = it->next;
    }
    _size = other._size;
    return *this;
}

template<typename T>
void queue<T>::swap(queue &other) {
    std::swap(_end, other._end);
    std::swap(_begin, other._begin);
    std::swap(_size, other._size);
}

template<typename T>
bool queue<T>::empty() {
    return !_size;
}

template<typename T>
T &queue<T>::front() {
    return _begin->data;
}

template<typename T>
T &queue<T>::back() {
    return _end->data;
}

template<typename T>
void queue<T>::pop() {
    if (_size > 1) {
        _begin = _begin->next;
        _size--;
    } else if (_size == 1) {
        _begin.reset();
        _end.reset();
        _begin = std::make_shared<Node>();
        _end = _begin;
        _size--;
    }
}

template<typename T>
void queue<T>::push(const T &value) {
    if (_size) {
        auto newNode = std::make_shared<Node>(value);
        newNode->data = value;
        newNode->prev = _end;
        _end->next = newNode;
        _end = newNode;
    } else {
        _begin->data = value;
    }
    _size++;
}

template<typename T>
queue<T>::queue(queue &&other) noexcept {
    _size = other._size;
    _begin = other._begin;
    _end = other._end;
    other._begin.reset();
    other._end.reset();
    other._size = 0;
}

template<typename T>
size_t queue<T>::size() const {
    return _size;
}

template<typename T>
queue<T>::queue(const queue &other) {
    _size = 0;
    _begin = std::make_shared<Node>(other._begin->data);
    _end = _begin;
    auto it = other._begin;
    for (size_t i = 0; i < other._size; ++i) {
        queue::push(it->data);
        it = it->next;
    }
    _size = other._size;
}

#endif//QUEUE_QUEUE_H
