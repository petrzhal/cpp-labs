#include <iostream>
#include "iterator.cpp"

template<typename T>
class vector : public it::const_iterator<T>
{
    T* _arr;
    size_t _size;
    size_t _capacity;
public:
    vector();
    ~vector();
    vector(const vector& other);
    vector(std::initializer_list<T> vec);
    vector& operator=(const vector& other);
    void push_back(const T& value);
    void pop_back();
    [[nodiscard]] size_t size() const;
    void reserve(int n);
    void resize(int n, const T& value = T());
    void erase(it::iterator<T> _iter);
    void erase(it::iterator<T> begin, it::iterator<T> end);
    [[nodiscard]] size_t max_size() const;
    void assign(size_t count, const T& value);
    template<class... Args>
    void emplace(it::iterator<T> pos, Args&&... args);
    template< class... Args >
    void emplace_back( Args&&... args );
    void clear();
    [[nodiscard]] size_t capacity();
    T& back();
    T& data();
    it::iterator<T> begin();
    it::iterator<T> end();
    it::const_iterator<T> cbegin() const;
    it::const_iterator<T> cend() const;
    T& operator[](int index);
    const T& operator[](int index) const;
    T& at(int index) const;
};

template<typename T>
template<typename... Args>
void vector<T>::emplace_back(Args &&...args) {
    T newObj(args...);
    vector::push_back(newObj);
}

template<typename T>
vector<T>::vector () {
    _arr = reinterpret_cast<T*>(new int8_t[sizeof(T)]);
    _capacity = 1;
    _size = 0;
}

template<typename T>
vector<T>::~vector() {
    for (int i = 0; i < _size; ++i) {
        (_arr + i)->~T();
    }
    delete[] reinterpret_cast<int8_t*>(_arr);
}

template<typename T>
vector<T>::vector(const vector& other) {
    if (this != &other) {
        _arr = reinterpret_cast<T*>(new int8_t[other._capacity * sizeof(T)]);
        for (int i = 0; i < other._size; ++i) {
            new (_arr + i) T(other[i]);
        }
        _size = other._size;
        _capacity = other._capacity;
    }
}

template<typename T>
vector<T>::vector(std::initializer_list<T> vec) {
    _size = _capacity = 0;
    reserve(vec.size());
    auto it = vec.begin();
    while (it != vec.end()) {
        push_back(*(it++));
    }
}

template<typename T>
vector<T>& vector<T>::operator=(const vector& other) {
    if (this != &other) {
        _arr = other._arr;
        _size = other._size;
        _capacity = other._capacity;
    }
    return *this;
}

template<typename T>
void vector<T>::push_back(const T& value) {
    if (_size >= _capacity)
        reserve(2 * _capacity);
    new (_arr + _size) T(value);
    ++_size;
}

template<typename T>
void vector<T>::pop_back() {
    --_size;
    (_arr + _size)->~T();
}

template<typename T>
[[nodiscard]] size_t vector<T>::size() const {
    return _size;
}

template<typename T>
void vector<T>::reserve(int n) {
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

template<typename T>
void vector<T>::resize(int n, const T& value) {
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

template<typename T>
void vector<T>::erase(it::iterator<T> _iter) {
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

template<typename T>
void vector<T>::erase(it::iterator<T> begin, it::iterator<T> end) {
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

template<typename T>
[[nodiscard]] size_t vector<T>::max_size() const {
    return 1;
}

template<typename T>
void vector<T>::assign(size_t count, const T& value) {
    clear();
    for (int i = 0; i < count; ++i) {
        push_back(value);
    }
}

template<typename T>
template<typename... Args>
void vector<T>::emplace(it::iterator<T> pos, Args&&... args) {
    pos.get()->~T();
    new (pos.get()) T(args...);
}

template<typename T>
void vector<T>::clear() {
    for (int i = 0; i < _size; ++i) {
        (_arr +i)->~T();
    }
    delete[] reinterpret_cast<int8_t*>(_arr);
    _arr = reinterpret_cast<T*>(new int8_t());
    _size = 0;
    _capacity = 1;
}

template<typename T>
[[nodiscard]] size_t vector<T>::capacity() {
    return _capacity;
}

template<typename T>
T& vector<T>::back() {
    return _arr[_size - 1];
}

template<typename T>
T& vector<T>::data() {
    return _arr[0];
}

template<typename T>
it::iterator<T> vector<T>::begin() {
    return it::IterFromPointer(_arr);
}

template<typename T>
it::iterator<T> vector<T>::end() {
    return it::IterFromPointer(_arr + _size);
}

template<typename T>
it::const_iterator<T> vector<T>::cbegin() const {
    return it::cIterFromPointer(_arr);
}

template<typename T>
it::const_iterator<T> vector<T>::cend() const {
    return it::cIterFromPointer(_arr + _size);
}

template<typename T>
T& vector<T>::operator[](int index)  {
    return _arr[index];
}

template<typename T>
const T& vector<T>::operator[](int index) const {
    return _arr[index];
}

template<typename T>
T& vector<T>::at(int index) const {
    if (index >= _size)
        throw std::out_of_range("index out of range: index = " + std::to_string(index) + ", _size = " + std::to_string(_size));
    return _arr[index];
}