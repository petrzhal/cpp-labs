#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <limits>
#include "iterator.cpp"
#include "allocator.cpp"

template<typename T, typename Alloc = allocator<T>>
class vector : public it::iterator<T>, public it::const_iterator<T>, public it::reverse_iterator<T> {
private:
    T *_arr;
    size_t _size;
    size_t _capacity;
    Alloc alloc;
public:
    explicit vector(const Alloc& = Alloc());
    ~vector();
    vector(it::iterator<T>, it::iterator<T>);
    vector(const vector &);
    vector(std::initializer_list<T>);
    vector &operator=(const vector &);
    void push_back(const T &);
    void pop_back();
    [[nodiscard]] size_t size() const;
    void reserve(size_t);
    void resize(size_t, const T& = T());
    void erase(it::iterator<T>);
    void erase(it::iterator<T>, it::iterator<T>);
    void insert(it::iterator<T>, const T&);
    template<typename InputIterator>
    void insert(const it::iterator<T> &, InputIterator, InputIterator);
    [[nodiscard]] size_t max_size() const;
    void assign(size_t, const T &);
    template<typename InputIterator>
    void assign(InputIterator, InputIterator);
    template<class... Args>
    void emplace(it::iterator<T>, Args &&...);
    template<class... Args>
    void emplace_back(Args &&...);
    void clear();
    [[nodiscard]] size_t capacity();
    void swap(const vector<T, Alloc>&);
    T &back();
    T *data();
    T &front();
    bool empty();
    it::iterator<T> begin();
    it::iterator<T> end();
    it::reverse_iterator<T> rbegin() const;
    it::reverse_iterator<T> rend() const;
    it::const_iterator<T> cbegin() const;
    it::const_iterator<T> cend() const;
    T &operator[](size_t);
    const T &operator[](size_t) const;
    T &at(size_t) const;
};

template<typename T, typename Alloc>
template<typename InputIterator>
void vector<T, Alloc>::assign(InputIterator _begin, InputIterator _end) {
    vector<T, Alloc>::clear();
    auto it = _begin;
    while (it != _end) {
        vector::push_back(*it++);
    }
}

template<typename T, typename Alloc>
it::reverse_iterator<T> vector<T, Alloc>::rbegin() const {
    return it::reverse_iterator<T>(_arr + _size - 1);
}

template<typename T, typename Alloc>
it::reverse_iterator<T> vector<T, Alloc>::rend() const {
    return it::reverse_iterator<T>(_arr - 1);
}

template<typename T, typename Alloc>
void vector<T, Alloc>::swap(const vector<T, Alloc> &other) {
    auto swpArr = _arr;
    _arr = other._arr;
    other._arr = swpArr;
    size_t swpCap = _capacity;
    _capacity = other._capacity;
    other._capacity = swpCap;
    size_t swpSize = _size;
    _size = other._size;
    other._size = swpSize;
}

template<typename T, typename Alloc>
void vector<T, Alloc>::insert(it::iterator<T> _pos, const T &value) {
    it::iterator<T> it = vector::begin();
    size_t ind = 0;
    while (it != _pos) {
        ind++;
        it++;
    }
    if (_capacity <= _size + 1)
        vector::reserve(_capacity * 2);
    it = vector::begin();
    for (size_t i = 0; i < ind; ++i) {
        it++;
    }
    size_t i;
    try {
        for (i = _size; i > ind; --i) {
            alloc.construct(_arr + i, _arr[i - 1]);
            alloc.destruct(_arr + i - 1);
        }
        alloc.construct(&*it, value);
        _size++;
    } catch (...) {
        vector::clear();
        throw;
    }
}

template<typename T, typename Alloc>
template<typename InputIterator>
void vector<T, Alloc>::insert(const it::iterator<T> &_pos, InputIterator _other_beg, InputIterator _other_end) {
    auto other = _other_beg;
    size_t count = 0;
    while (other != _other_end) {
        other++;
        count++;
    }
    it::iterator<T> it = vector::begin();
    size_t ind = 0;
    while (it != _pos) {
        ind++;
        it++;
    }
    if (_size + count >= _capacity)
        vector::reserve(_capacity * 2);
    try {
        for (size_t i = _size - 1 + count; i > ind; --i) {
            alloc.construct(_arr + i, _arr[i - count]);
            alloc.destruct(_arr + i - count);
        }
        other = _other_beg;
        for (size_t i = ind; other != _other_end; ++i) {
            alloc.construct(&_arr + i, *(other++));
        }
        _size += count;
    } catch (...) {
        vector::clear();
        throw;
    }
}

template<typename T, typename Alloc>
bool vector<T, Alloc>::empty() {
    if (!_size)
        return true;
    return false;
}

template<typename T, typename Alloc>
T &vector<T, Alloc>::front() {
    return _arr[0];
}

template<typename T, typename Alloc>
template<typename... Args>
void vector<T, Alloc>::emplace_back(Args &&...args) {
    if (_size + 1 >= _capacity)
        vector::reserve(_capacity * 2);
    try {
        alloc.construct(_arr + _size, args...);
    }
    catch (...) {
        alloc.destruct(_arr + _size);
        throw;
    }
    _size++;
}

template<typename T, typename Alloc>
vector<T, Alloc>::vector(const Alloc& alloc) : alloc(alloc) {
    vector::reserve(1);
    _capacity = 1;
    _size = 0;
}

template<typename T, typename Alloc>
vector<T, Alloc>::~vector() {
    for (size_t i = 0; i < _size; ++i) {
        alloc.destruct(_arr + i);
    }
    alloc.deallocate(_arr);
}

template<typename T, typename Alloc>
vector<T, Alloc>::vector(it::iterator<T> _beg, it::iterator<T> _end) {
    _size = 0;
    _capacity = 0;
    auto it = _beg;
    while (it != _end) {
        vector::push_back(*it);
        it++;
    }
}

template<typename T, typename Alloc>
vector<T, Alloc>::vector(const vector &other) {
    if (this != &other) {
        try {
            _arr = alloc.allocate(other._capacity);
            for (size_t i = 0; i < other._size; ++i) {
                alloc.construct(_arr + i, other._arr[i]);
            }
            _size = other._size;
            _capacity = other._capacity;
        } catch (...) {
            vector::clear();
            throw;
        }
    }
}

template<typename T, typename Alloc>
vector<T, Alloc>::vector(std::initializer_list<T> vec) {
    _size = _capacity = 0;
    vector::reserve(vec.size());
    auto it = vec.begin();
    while (it != vec.end()) {
        push_back(*(it++));
    }
}

template<typename T, typename Alloc>
vector<T, Alloc> &vector<T, Alloc>::operator=(const vector &other) {
    if (this != &other) {
        try {
            vector::clear();
            vector::reserve(other._capacity);
            vector::resize(other._size);
            for (size_t i = 0; i < other._size; ++i) {
                alloc.construct(_arr + i, other._arr[i]);
            }
        } catch (...) {
            vector::clear();
            throw;
        }
    }
    return *this;
}

template<typename T, typename Alloc>
void vector<T, Alloc>::push_back(const T &value) {
    vector::emplace_back(value);
}

template<typename T, typename Alloc>
void vector<T, Alloc>::pop_back() {
    --_size;
    alloc.destruct(_arr + _size);
}

template<typename T, typename Alloc>
[[nodiscard]] size_t vector<T, Alloc>::size() const {
    return _size;
}

template<typename T, typename Alloc>
void vector<T, Alloc>::reserve(size_t n) {
    if (n <= _capacity)
        return;
    auto new_arr = alloc.allocate(n);
    size_t i;
    try {
        for (i = 0; i < size(); ++i) {
            alloc.construct(new_arr + i, _arr[i]);
        }
    } catch (...) {
        for (size_t j = 0; j < i; ++j) {
            alloc.destruct(new_arr + j);
        }
        alloc.deallocate(new_arr);
        throw;
    }
    _arr = new_arr;
    _capacity = n;
}

template<typename T, typename Alloc>
void vector<T, Alloc>::resize(size_t n, const T &value) {
    if (n < _size) {
        for (size_t i = n - 1; i < _size; ++i) {
            alloc.destruct(_arr + i);
        }
    } else if (n > _size) {
        try {
            while (n >= _capacity)
                reserve(_capacity * 2);
            for (size_t i = _size; i < n; ++i) {
                alloc.construct(_arr + i, value);
            }
        } catch (...) {
            vector::clear();
            throw;
        }
    }
    _size = n;
}

template<typename T, typename Alloc>
void vector<T, Alloc>::erase(it::iterator<T> _iter) {
    size_t ind = 0;
    for (auto it = vector::begin(); it != _iter && ind < _size; ++it) {
        ind++;
    }
    alloc.destruct(_iter.get_pointer());
    try {
        for (size_t i = ind + 1; i < _size; ++i) {
            alloc.construct(_arr + i - 1, _arr[i]);
            alloc.destruct(_arr + i);
        }
        _size--;
    } catch (...) {
        vector::clear();
        throw;
    }
}

template<typename T, typename Alloc>
void vector<T, Alloc>::erase(it::iterator<T> begin, it::iterator<T> end) {
    size_t ind = 0;
    for (auto it = vector::begin(); it != end; ++it) {
        ind++;
    }
    size_t count = 0;
    for (auto it = begin; it != end; ++it) {
        alloc.destruct(it);
        count++;
    }
    try {
        for (size_t i = ind; i < _size; ++i) {
            alloc.construct(_arr + i - count, _arr[i]);
            alloc.destruct(_arr + i);
        }
    }
    catch (...) {
        vector::clear();
        throw;
    }
    _size -= count;
}

template<typename T, typename Alloc>
[[nodiscard]] size_t vector<T, Alloc>::max_size() const {
    return std::numeric_limits<size_t>::max() / sizeof(T);
}

template<typename T, typename Alloc>
void vector<T, Alloc>::assign(size_t count, const T &value) {
    vector::clear();
    for (size_t i = 0; i < count; ++i) {
        push_back(value);
    }
}

template<typename T, typename Alloc>
template<typename... Args>
void vector<T, Alloc>::emplace(it::iterator<T> pos, Args &&...args) {
    try {
        vector::insert(pos, T(args...));
    }
    catch (...) {
        vector::clear();
        throw;
    }
}

template<typename T, typename Alloc>
void vector<T, Alloc>::clear() {
    for (size_t i = 0; i < _size; ++i) {
        alloc.destruct(_arr + i);
    }
    _size = 0;
}

template<typename T, typename Alloc>
[[nodiscard]] size_t vector<T, Alloc>::capacity() {
    return _capacity;
}

template<typename T, typename Alloc>
T &vector<T, Alloc>::back() {
    return _arr[_size - 1];
}

template<typename T, typename Alloc>
T *vector<T, Alloc>::data() {
    return &_arr[0];
}

template<typename T, typename Alloc>
it::iterator<T> vector<T, Alloc>::begin() {
    return it::iterator(_arr);
}

template<typename T, typename Alloc>
it::iterator<T> vector<T, Alloc>::end() {
    return it::iterator(_arr + _size);
}

template<typename T, typename Alloc>
it::const_iterator<T> vector<T, Alloc>::cbegin() const {
    return it::const_iterator(_arr);
}

template<typename T, typename Alloc>
it::const_iterator<T> vector<T, Alloc>::cend() const {
    return it::const_iterator(_arr + _size);
}

template<typename T, typename Alloc>
T &vector<T, Alloc>::operator[](size_t index) {
    return _arr[index];
}

template<typename T, typename Alloc>
const T &vector<T, Alloc>::operator[](size_t index) const {
    return _arr[index];
}

template<typename T, typename Alloc>
T &vector<T, Alloc>::at(size_t index) const {
    if (index >= _size)
        throw std::out_of_range("index out of range");
    return _arr[index];
}

#endif // VECTOR_H
