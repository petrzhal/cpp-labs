#ifndef HASH_STACK_H
#define HASH_STACK_H
#include <iostream>
#include <memory>

template<class T>
class stack {
private:
    struct Node {
        Node *_next;
        T _data;
        Node()
            : _next(nullptr),
              _data(T()) {}
        explicit Node(const T &data)
            : _data(data),
              _next(nullptr) {}
    };

    size_t _size;
    Node *_top;

public:
    stack()
        : _size(0),
          _top(new Node()) {}
    stack(const stack &other) {
        if (!other._top) {
            _top = nullptr;
            _size = 0;
        } else {
            auto tmp = other._top;
            auto tmp2 = new Node(tmp->_data);
            tmp = tmp->_next;
            _top = tmp2;
            _size = other._size;
            while (tmp) {
                tmp2->_next = new Node();
                tmp2 = tmp2->_next;
                tmp2->_data = tmp->_data;
                tmp = tmp->_next;
            }
            tmp2->_next = nullptr;
        }
    }
    stack &operator=(const stack &other) {
        if (this != &other) {
            clear();
            delete _top;
            if (!other._top) {
                _top = nullptr;
                _size = 0;
            } else {
                auto tmp = other._top;
                auto tmp2 = new Node(tmp->_data);
                tmp = tmp->_next;
                _top = tmp2;
                _size = other._size;
                while (tmp) {
                    tmp2->_next = new Node();
                    tmp2 = tmp2->_next;
                    tmp2->_data = tmp->_data;
                    tmp = tmp->_next;
                }
                tmp2->_next = nullptr;
            }
        }
        return *this;
    }
    ~stack() {
        Node *tmp = _top;
        for (int i = 0; i < _size; ++i) {
            Node *buf = tmp->_next;
            delete tmp;
            tmp = buf;
        }
    }
    void push(const T &newElement) {
        auto newEl = new Node(newElement);
        if (_size > 0) {
            newEl->_next = _top;
            _top = newEl;
        } else {
            newEl->_next = nullptr;
            _top = newEl;
        }
        _size++;
    }
    T &top() {
        if (_top)
            return _top->_data;
        else {
            _top = new Node();
            return _top->_data;
        }
    }
    T pop() {
        if (_size) {
            auto rem = _top->_data;
            Node *tmp = _top->_next;
            delete _top;
            _top = tmp;
            _size--;
            return rem;
        } else
            return T();
    }
    int size() {
        return _size;
    }
    [[nodiscard]] bool empty() const {
        return !_size;
    }
    void clear() {
        while (_size) {
            pop();
        }
        _top = new Node();
    }
};

#endif//HASH_STACK_H
