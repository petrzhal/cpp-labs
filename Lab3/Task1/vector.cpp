#include <iostream>
#include "iterator.cpp"

template<typename T>
class vector : public it::reverse_iterator<T>
{
    T* _arr;
    size_t _size;
    size_t _capacity;
public:
    vector();
    ~vector();
    vector(const vector&);
    vector(std::initializer_list<T>);
    vector& operator=(const vector&);
    void push_back(const T&);
    void pop_back();
    [[nodiscard]] size_t size() const;
    void reserve(int);
    void resize(int, const T& = T());
    void erase(it::iterator<T>);
    void erase(it::iterator<T>, it::iterator<T>);
    void insert(it::iterator<T>, const T& value);
    template<typename InputIterator>
    void insert(const it::iterator<T>&, InputIterator, InputIterator);
    [[nodiscard]] size_t max_size() const;
    void assign(size_t, const T&);
    template<class... Args>
    void emplace(it::iterator<T>, Args&&...);
    template< class... Args>
    void emplace_back(Args&&...);
    void clear();
    [[nodiscard]] size_t capacity();
    void swap(const vector<T>&);
    T& back();
    T* data();
    T& front();
    bool empty();
    it::iterator<T> begin() const;
    it::iterator<T> end() const;
    it::reverse_iterator<T> rbegin() const;
    it::reverse_iterator<T> rend() const;
    it::const_iterator<T> cbegin() const;
    it::const_iterator<T> cend() const;
    T& operator[](int);
    const T& operator[](int) const;
    T& at(int) const;
};

template<typename T>
it::reverse_iterator<T> vector<T>::rbegin() const {
    return it::reverse_iterator<T>(_arr + _size - 1);
}

template<typename T>
it::reverse_iterator<T> vector<T>::rend() const {
    return it::reverse_iterator<T>(_arr - 1);
}

template<typename T>
void vector<T>::swap(const vector<T> & other) {
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

template<typename T>
void vector<T>::insert(it::iterator<T> _pos, const T& value) {
    it::iterator<T> it = vector::begin();
    size_t ind = 0;
    while (it != _pos) {
        ind++;
        it++;
    }
    if (_capacity <= _size + 1)
        vector::reserve(_capacity * 2);
    it = vector::begin();
    for (int i = 0; i < ind; ++i) {
        it++;
    }
    size_t i;
    try {
        for (i = _size; i > ind; --i) {
            new (&_arr[i]) T(_arr[i - 1]);
            (_arr + i - 1)->~T();
        }
        new (&*it) T(value);
        _size++;
    } catch (...) {
        vector::clear();
        throw;
    }
}

template<typename T>
template<typename InputIterator>
void vector<T>::insert(const it::iterator<T>& _pos, InputIterator _other_beg, InputIterator _other_end) {
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
            new (&_arr[i]) T(_arr[i - count]);
            (_arr + i - count)->~T();
        }
        other = _other_beg;
        for (size_t i = ind; other != _other_end; ++i) {
            new (_arr + i) T(*(other++));
        }
        _size += count;
    } catch (...) {
        vector::clear();
        throw;
    }
}

template<typename T>
bool vector<T>::empty() {
    if (!_size)
        return true;
    return false;
}

template<typename T>
T &vector<T>::front() {
    return _arr[0];
}

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
        try {
            _arr = reinterpret_cast<T *>(new int8_t[other._capacity * sizeof(T)]);
            for (int i = 0; i < other._size; ++i) {
                new (_arr + i) T(other._arr[i]);
            }
            _size = other._size;
            _capacity = other._capacity;
        } catch (...) {
            vector::clear();
            throw;
        }
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
        try {
            vector::clear();
            vector::reserve(other._capacity);
            vector::resize(other._size);
            for (int i = 0; i < other._size; ++i) {
                new (_arr + i) T(other._arr[i]);
            }
        } catch (...) {
            vector::clear();
            throw;
        }
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
    if (n <= _capacity)
        return;
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
        try {
            if (n <= _capacity)
                reserve(_capacity * 2);
            for (int i = _size; i < n; ++i) {
                new (_arr + i) T(value);
            }
        } catch (...) {
            vector::clear();
            throw;
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
    try {
        for (size_t i = ind + 1; i < _size; ++i) {
            new (_arr + i - 1) T(_arr[i]);
            (_arr + i)->~T();
        }
        _size--;
    } catch (...) {
        vector::clear();
        throw;
    }
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
    return ULLONG_MAX;
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
    pos.get_pointer()->~T();
    new (pos.get_pointer()) T(args...);
}

template<typename T>
void vector<T>::clear() {
    for (int i = 0; i < _size; ++i) {
        (_arr + i)->~T();
    }
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
T* vector<T>::data() {
    return &_arr[0];
}

template<typename T>
it::iterator<T> vector<T>::begin() const {
    return it::iterator(_arr);
}

template<typename T>
it::iterator<T> vector<T>::end() const {
    return it::iterator(_arr + _size);
}

template<typename T>
it::const_iterator<T> vector<T>::cbegin() const {
    return it::const_iterator(_arr);
}

template<typename T>
it::const_iterator<T> vector<T>::cend() const {
    return it::const_iterator(_arr + _size);
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
        throw std::out_of_range("index out of range");
    return _arr[index];
}
