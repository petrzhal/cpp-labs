#include "allocator.cpp"
#include "iterator.cpp"
#include <cstring>
#include <limits>
#include <ostream>

template<typename CharT, class Allocator = allocator<CharT>>
class basic_string {
private:
    CharT *_base = nullptr;
    size_t _size = 0;
    size_t _capacity = 0;
    Allocator alloc;

public:
    static const size_t npos = -1;
    explicit basic_string(const Allocator & = Allocator());
    basic_string(const char *);
    ~basic_string();
    basic_string(const basic_string &);
    basic_string(basic_string &&) noexcept;
    basic_string &operator=(const basic_string &);
    basic_string &operator=(basic_string &&) noexcept;
    [[nodiscard]] size_t size() const;
    void reserve(size_t);
    void resize(size_t);
    void resize(size_t, CharT);
    void push_back(const CharT &);
    void append(const basic_string&);
    void append(size_t, CharT);
    CharT &operator[](size_t);
    iterator<CharT> begin();
    iterator<CharT> end();
    reverse_iterator<CharT> rbegin();
    reverse_iterator<CharT> rend();
    const_iterator<CharT> cbegin();
    const_iterator<CharT> cend();
    basic_string operator+(const basic_string &);
    [[nodiscard]] size_t capacity();
    [[nodiscard]] size_t length();
    basic_string &operator+=(const basic_string &);
    void clear();
    void erase(size_t = 0, size_t = npos);
    void insert(size_t, basic_string);
    int compare(const basic_string&);
    CharT &front() const;
    CharT &back() const;
    CharT* data() const;
    const CharT *c_str();
    bool empty();
    void shrink_to_fit();
    [[nodiscard]] size_t max_size();
    void pop_back();
    void replace(size_t, size_t, const basic_string &);
    basic_string substr(size_t = 0, size_t = npos);
    friend std::ostream &operator<<(std::ostream &os, const basic_string &basicString) {
        for (size_t i = 0; i < basicString._size; ++i)
            os << basicString._base[i];
        return os;
    }
    friend std::istream &operator>>(std::istream &is, basic_string &basicString) {
        is >> basicString._base;
        basicString._size = strlen(basicString._base);
        basicString._capacity = basicString._size;
        return is;
    }
};

template<typename CharT, class Allocator>
int basic_string<CharT, Allocator>::compare(const basic_string &s) {
    size_t lhs_sz = size();
    size_t rhs_sz = s.size();
    int result = std::char_traits<CharT>::compare(data(), s.data(), std::min(lhs_sz, rhs_sz));
    if (result != 0)
        return result;
    if (lhs_sz < rhs_sz)
        return -1;
    if (lhs_sz > rhs_sz)
        return 1;
    return 0;
}

template<typename CharT, class Allocator>
reverse_iterator<CharT> basic_string<CharT, Allocator>::rend() {
    return reverse_iterator<CharT>(_base - 1);
}

template<typename CharT, class Allocator>
reverse_iterator<CharT> basic_string<CharT, Allocator>::rbegin() {
    return reverse_iterator<CharT>(_base + _size - 1);
}

template<typename CharT, class Allocator>
const_iterator<CharT> basic_string<CharT, Allocator>::cend() {
    return const_iterator<CharT>(_base + _size);
}

template<typename CharT, class Allocator>
const_iterator<CharT> basic_string<CharT, Allocator>::cbegin() {
    return const_iterator<CharT>(_base);
}

template<typename CharT, class Allocator>
void basic_string<CharT, Allocator>::append(size_t count, CharT c) {
    while (_capacity <= _size + count)
        basic_string::reserve(_capacity * 2);
    for (size_t i = _size; i < _size + count; ++i) {
        alloc.construct(_base + i, c);
    }
    _size += count;
}

template<typename CharT, class Allocator>
void basic_string<CharT, Allocator>::append(const basic_string &str) {
    while (_capacity <= _size + str._size)
        basic_string::reserve(_capacity * 2);
    basic_string::insert(_size, str);
}

template<typename CharT, class Allocator>
CharT *basic_string<CharT, Allocator>::data() const {
    return _base;
}

template<typename CharT, class Allocator>
basic_string<CharT, Allocator>::~basic_string() {
    alloc.deallocate(_base);
    _capacity = _size = 0;
}

template<typename CharT, class Allocator>
basic_string<CharT, Allocator> basic_string<CharT, Allocator>::substr(size_t index, size_t count) {
    basic_string substr;
    size_t offset = std::min(count, _size - index);
    for (size_t i = index; i < offset + index; ++i) {
        substr.push_back(_base[i]);
    }
    return substr;
}

template<typename CharT, class Allocator>
void basic_string<CharT, Allocator>::replace(size_t index, size_t count, const basic_string &str) {
    basic_string::erase(index, count);
    basic_string::insert(index, str);
}

template<typename CharT, class Allocator>
void basic_string<CharT, Allocator>::pop_back() {
    _size--;
}

template<typename CharT, class Allocator>
void basic_string<CharT, Allocator>::shrink_to_fit() {
    CharT *newBase = alloc.allocate(_size);
    for (size_t i = 0; i < _size; ++i) {
        alloc.construct(newBase + i, _base[i]);
    }
    _capacity = _size;
}

template<typename CharT, class Allocator>
size_t basic_string<CharT, Allocator>::max_size() {
    return std::numeric_limits<std::size_t>::max();
}

template<typename CharT, class Allocator>
bool basic_string<CharT, Allocator>::empty() {
    return !_size;
}

template<typename CharT, class Allocator>
const CharT *basic_string<CharT, Allocator>::c_str() {
    CharT *c_str = alloc.allocate(_size + 1);
    for (size_t i = 0; i < _size; ++i) {
        c_str[i] = _base[i];
    }
    c_str[_size] = '\0';
    return c_str;
}

template<typename CharT, class Allocator>
CharT &basic_string<CharT, Allocator>::back() const {
    return _base[_size - 1];
}

template<typename CharT, class Allocator>
CharT &basic_string<CharT, Allocator>::front() const {
    return _base[0];
}

template<typename CharT, class Allocator>
void basic_string<CharT, Allocator>::resize(size_t n) {
    if (n > _size) {
        while (_capacity <= n)
            basic_string::reserve(_capacity * 2);
    }
    _size = n;
}

template<typename CharT, class Allocator>
void basic_string<CharT, Allocator>::resize(size_t n, CharT c) {
    if (n > _size) {
        while (_capacity <= n)
            basic_string::reserve(_capacity * 2);
        for (size_t i = _size; i < n; ++i) {
            _base[i] = c;
        }
    }
    _size = n;
}

template<typename CharT, class Allocator>
void basic_string<CharT, Allocator>::insert(size_t index, basic_string str) {
    while (_capacity <= _size + str._size)
        basic_string::reserve(_capacity * 2);
    for (size_t i = _size; i > index; --i) {
        alloc.construct(_base + i - 1 + str._size, _base[i - 1]);
    }
    size_t otherInd = 0;
    for (size_t i = index; otherInd < str._size; ++i, ++otherInd) {
        alloc.construct(_base + i, str._base[otherInd]);
    }
    _size += str._size;
}

template<typename CharT, class Allocator>
void basic_string<CharT, Allocator>::erase(size_t index, size_t count) {
    size_t offset = std::min(count, _size - index);
    for (size_t i = index; i < _size; ++i) {
        alloc.construct(_base + i, _base[i + offset]);
    }
    _size -= offset;
}

template<typename CharT, class Allocator>
void basic_string<CharT, Allocator>::clear() {
    alloc.deallocate(_base);
    _base = nullptr;
    _size = 0;
    _base = alloc.allocate(1);
    _capacity = 1;
}

template<typename CharT, class Allocator>
basic_string<CharT, Allocator> &basic_string<CharT, Allocator>::operator+=(const basic_string &other) {
    while (_size + other._size >= _capacity)
        basic_string::reserve(_capacity * 2);
    size_t otherInd = 0;
    for (size_t i = _size; i < _size + other._size; ++i) {
        alloc.construct(_base + i, other._base[otherInd++]);
    }
    _size += other._size;
    return *this;
}

template<typename CharT, class Allocator>
size_t basic_string<CharT, Allocator>::length() {
    return _size;
}

template<typename CharT, class Allocator>
size_t basic_string<CharT, Allocator>::capacity() {
    return _capacity;
}

template<typename CharT, class Allocator>
basic_string<CharT, Allocator> basic_string<CharT, Allocator>::operator+(const basic_string &other) {
    basic_string newStr(*this);
    newStr.operator+=(other);
    return newStr;
}

template<typename CharT, class Allocator>
iterator<CharT> basic_string<CharT, Allocator>::end() {
    return iterator<CharT>(_base + _size);
}

template<typename CharT, class Allocator>
iterator<CharT> basic_string<CharT, Allocator>::begin() {
    return iterator<CharT>(_base);
}

template<typename CharT, class Allocator>
CharT &basic_string<CharT, Allocator>::operator[](size_t ind) {
    return _base[ind];
}

template<typename CharT, class Allocator>
void basic_string<CharT, Allocator>::push_back(const CharT &ch) {
    if (_size >= _capacity)
        basic_string::reserve(_capacity * 2);
    alloc.construct(_base + _size, ch);
    _size++;
}

template<typename CharT, class Allocator>
size_t basic_string<CharT, Allocator>::size() const {
    return _size;
}

template<typename CharT, class Allocator>
void basic_string<CharT, Allocator>::reserve(size_t n) {
    if (n > _capacity) {
        auto new_base = alloc.allocate(n);
        for (size_t i = 0; i < basic_string::size(); ++i) {
            alloc.construct(new_base + i, _base[i]);
        }
        alloc.deallocate(_base);
        _base = new_base;
        _capacity = n;
    }
}

template<typename CharT, class Allocator>
basic_string<CharT, Allocator>::basic_string(const char *str) {
    size_t length = strlen(str);
    basic_string::reserve(length);
    for (int i = 0; i < length; ++i) {
        alloc.construct(_base + i, str[i]);
    }
    _size = length;
    _capacity = length;
}

template<typename CharT, class Allocator>
basic_string<CharT, Allocator>::basic_string(const Allocator &alloc) : _base(alloc.allocate(1)), _size(0), _capacity(1), alloc(alloc) {}

template<typename CharT, class Allocator>
basic_string<CharT, Allocator>::basic_string(const basic_string &other) {
    alloc.deallocate(_base);
    basic_string::reserve(other._capacity);
    _size = other._size;
    for (int i = 0; i < _size; ++i) {
        alloc.construct(_base + i, other._base[i]);
    }
}

template<typename CharT, class Allocator>
basic_string<CharT, Allocator>::basic_string(basic_string &&other) noexcept {
    alloc.deallocate(_base);
    _base = other._base;
    _capacity = other._capacity;
    _size = other._size;
    other._capacity = other._size = 0;
    other._base = nullptr;
}

template<typename CharT, class Allocator>
basic_string<CharT, Allocator> &basic_string<CharT, Allocator>::operator=(const basic_string &other) {
    if (this != other) {
        alloc.deallocate(_base);
        basic_string::reserve(other._capacity);
        _size = other._size;
        for (int i = 0; i < _size; ++i) {
            alloc.construct(_base + i, other._base[i]);
        }
    }
    return *this;
}

template<typename CharT, class Allocator>
basic_string<CharT, Allocator> &basic_string<CharT, Allocator>::operator=(basic_string &&other) noexcept {
    alloc.deallocate(_base);
    _base = other._base;
    _capacity = other._capacity;
    _size = other._size;
    other._capacity = other._size = 0;
    other._base = nullptr;
    return *this;
}

typedef basic_string<char> string;