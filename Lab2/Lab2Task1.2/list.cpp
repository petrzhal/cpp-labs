#include <iostream>
#include "member.h"

#define null -1

class list {
private:
    struct elem {
        Member data;
        int next;
        int prev;
    };

    elem *_arr;
    int _begin;
    int _end;
    int _size;

    int Move(int ind) {
        int it = _begin;
        for (int i = 0; i < ind; ++i) {
            it = _arr[it].next;
        }
        return it;
    }

    bool IsCorrectIndex(int i) {
        return (i <= _size) && (i >= 0);
    }

public:
    list() {
        _arr = nullptr;
        _begin = null;
        _end = null;
        _size = 0;
    }

    list(const list &lst) {
        elem *newArr = new elem[lst._size];
        for (int i = 0; i < lst._size; ++i) {
            newArr[i] = lst._arr[i];
        }
        _begin = lst._begin;
        _end = lst._end;
        _size = lst._size;
    }

    void push_back(const Member &data) {
        elem *newArr = new elem[_size + 1];
        for (int i = 0; i < _size; ++i) {
            newArr[i] = _arr[i];
        }
        newArr[_size].data = data;
        if (!_size) {
            newArr[_size].prev = null;
            newArr[_size].next = null;
            _begin = _end = _size;
        } else {
            newArr[_size].prev = _end;
            newArr[_size].next = null;
            newArr[_end].next = _size;
            _end = _size;
        }
        _arr = newArr;
        _size++;
    }

    void push_front(const Member &data) {
        elem *newArr = new elem[_size + 1];
        for (int i = 0; i < _size; ++i) {
            newArr[i] = _arr[i];
        }
        newArr[_size].data = data;
        if (!_size) {
            newArr[_size].prev = null;
            newArr[_size].next = null;
            _begin = _end = _size;
        } else {
            newArr[_size].prev = null;
            newArr[_size].next = _begin;
            newArr[_begin].prev = 0;
            _begin = _size;
        }
        _arr = newArr;
        _size++;
    }

    /*void insert(const Member &data, int index) {
        if (!IsCorrectIndex(index))
            throw std::out_of_range("index out of range");

        if (index == _size) {
            push_back(data);
            return;
        } else if (index == 0) {
            push_front(data);
            return;
        } else {
            elem *newArr = new elem[_size + 1];
            for (int i = 0; i < _size + 1; ++i) {
                newArr[i] = _arr[i];
            }
            newArr[_size].data = data;
            int elemPrev = Move(index - 1);
            int elemNext = Move(index);
            newArr[_size].prev = elemPrev;
            newArr[_size].next = elemNext;
            newArr[elemPrev] = _size;
            newArr[elemNext] = _size;
            _arr = newArr;
            _size++;
        }
    }*/

    void erase(int index) {
        if (!_size || (index < 0 && index >= _size))
            return;
        if (!index) {
            _arr[_arr[_begin].next].prev = null;
            _begin = Move(index + 1);
        } else if (index == _size - 1) {
            _arr[Move(_end - 1)].next = null;
            _end = Move(index - 1);
        } else {
            int next = _arr[Move(index)].next;
            int prev = _arr[Move(index)].prev;
            _arr[Move(index - 1)].next = next;
            _arr[Move(index + 1)].prev = prev;
        }
        _size--;
    }

    void clear() {
        delete[] _arr;
        _size = 0;
        _begin = null;
        _end = null;
    }

    Member &at(int index) {
        if (!IsCorrectIndex(index))
            throw std::out_of_range("index out of range");
        return _arr[Move(index)].data;
    }

    /*void print(const std::string &message) {
        std::cout << message;
        for (int i = 0; i < _size; ++i) {
            std::cout << at(i) << " ";
        }
    }

    void print() {
        for (int i = 0; i < _size; ++i) {
            std::cout << at(i) << " ";
        }
        std::cout << "\n";
    }*/

    [[nodiscard]] int size() const {
        return _size;
    }

    elem *begin() {
        return &_arr[_begin];
    }

    elem *end() {
        return &_arr[_end];
    }

    list &operator=(const list &other) {
        _arr = other._arr;
        _begin = other._begin;
        _end = other._end;
        _size = other._size;
        return *this;
    }

    Member &operator[](int ind) {
        return at(ind);
    }
};
