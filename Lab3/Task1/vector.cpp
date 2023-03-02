#include <iostream>
#include "iterator.cpp"

template<class T>
class vector : public it::iterator<T>, public it::const_iterator<T>
{
    T* _arr;
    size_t _size;
    size_t _capacity;
public:
    vector() {
        _arr = reinterpret_cast<T*>(new int8_t[sizeof(T)]);
        _capacity = 1;
        _size = 0;
    }

    ~vector() {
        for (int i = 0; i < _size; ++i) {
            (_arr + i)->~T();
        }
        delete[] reinterpret_cast<int8_t*>(_arr);
    }

    vector(const vector& other) {
        if (this != &other) {
            _arr = reinterpret_cast<T*>(new int8_t[other._capacity * sizeof(T)]);
            for (int i = 0; i < other._size; ++i) {
                new (_arr + i) T(other[i]);
            }
            _size = other._size;
            _capacity = other._capacity;
        }
    }

    vector(std::initializer_list<T> vec) {
        _size = _capacity = 0;
        reserve(vec.size());
        auto it = vec.begin();
        while (it != vec.end()) {
            push_back(*(it++));
        }
    }

    vector& operator=(const vector& other) {
        if (this != &other) {
            _arr = other._arr;
            _size = other._size;
            _capacity = other._capacity;
        }
        return *this;
    }

    void push_back(const T& value) {
        if (_size >= _capacity)
            reserve(2 * _capacity);
        new (_arr + _size) T(value);
        ++_size;
    }

    void pop_back() {
        --_size;
        (_arr + _size)->~T();
    }

    [[nodiscard]] size_t size() const {
        return _size;
    }

    void reserve(int n) {
        T* new_arr = reinterpret_cast<T*>(new int8_t [n * sizeof(T)]);
        int i;
        try {
            for (i = 0; i < size(); ++i) {
                new (new_arr + i) T(_arr[i]);
            }
        } catch (...) {
            for (int j = 0; j < i; ++j) {
                (new_arr + j)->~T();
            }
            delete[] reinterpret_cast<int8_t*>(new_arr);
            throw;
        }
        _arr = new_arr;
        _capacity = n;
    }

    void resize(int n, const T& value = T()) {
        if (n < _size) {
            for (int i = n - 1; i < _size; ++i) {
                (_arr + i)->~T();
            }
        }
        else if (n > _size) {
            if (n <= _capacity)
                reserve(_capacity * 2);
            for (int i = _size; i < n; ++i) {
                new (_arr + i) T(value);
            }
        }
        _size = n;
    }

    void erase(it::iterator<T> _iter) {
        size_t ind = 0;
        for (auto it = begin(); it != _iter && ind < _size; ++it) {
            ind++;
        }
        _iter->~T();
        for (size_t i = ind + 1; i < _size; ++i) {
            new (_arr + i - 1) T(_arr[i]);
            (_arr + i)->~T();
        }
        _size--;
    }

    void erase(it::iterator<T> begin, it::iterator<T> end) {
        size_t ind = 0;
        for (auto it = vector::begin(); it != end; ++it) {
            ind++;
        }
        size_t count = 0;
        for (auto it = begin; it != end; ++it) {
            it->~T();
            count++;
        }
        for (size_t i = ind; i < _size; ++i) {
            new (_arr + i - count) T(_arr[i]);
            (_arr + i)->~T();
        }
        _size -= count;
    }

    [[nodiscard]] size_t max_size() const {
        return 1;
    }

    void assign(size_t count, const T& value) {
        clear();
        for (int i = 0; i < count; ++i) {
            push_back(value);
        }
    }

    void clear() {
        for (int i = 0; i < _size; ++i) {
            (_arr +i)->~T();
        }
        delete[] reinterpret_cast<int8_t*>(_arr);
        _arr = reinterpret_cast<T*>(new int8_t());
        _size = 0;
        _capacity = 1;
    }

    T& back() {
        return _arr[_size - 1];
    }

    it::iterator<T> begin() {
        return it::IterFromPointer(_arr);
    }

    it::iterator<T> end() {
        return it::IterFromPointer(_arr + _size);
    }

    it::const_iterator<T> begin() const {
        return it::cIterFromPointer(_arr);
    }

    it::const_iterator<T> end() const {
        return it::cIterFromPointer(_arr + _size);
    }

    T& operator[](int index)  {
        return _arr[index];
    }

    const T& operator[](int index) const {
        return _arr[index];
    }

    T& at(int index) const {
        if (index >= _size)
            throw std::out_of_range("index out of range: index = " + std::to_string(index) + ", _size = " + std::to_string(_size));
        return _arr[index];
    }
};
