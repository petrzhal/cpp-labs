#ifndef DEQUE_H
#define DEQUE_H

#include "allocator.cpp"
#include <iostream>

template<typename T, size_t N = 32, class Allocator = allocator<T>>
class deque {
public:
    class deque_iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = value_type *;
        using reference = value_type &;

    private:
        const deque<T, N>* ptr;
        size_t index;

    public:
        deque_iterator() : ptr(nullptr), index(0) {}

        deque_iterator(const deque_iterator &other) {
            ptr = other.ptr;
            index = other.index;
        }

        deque_iterator(deque_iterator &&other) noexcept {
            ptr = other.ptr;
            index = other.index;
            other.ptr = nullptr;
            other.index = 0;
        }

        explicit deque_iterator(const deque* ptr, size_t ind)
            : ptr(ptr),
              index(ind) {}

        deque_iterator &operator++() {
            index++;
            return *this;
        }

        deque_iterator &operator--() {
            index--;
            return *this;
        }

        deque_iterator operator++(int) {
            deque_iterator old = *this;
            index++;
            return old;
        }

        deque_iterator operator--(int) {
            deque_iterator old = *this;
            index--;
            return old;
        }

        bool operator<(const deque_iterator& other) {
            return index < other.index;
        }

        bool operator>(const deque_iterator& other) {
            return index > other.index;
        }

        bool operator!=(const deque_iterator& other) {
            return index != other.index;
        }

        bool operator==(const deque_iterator& other) {
            return index == other.index;
        }

        deque_iterator &operator=(const deque_iterator &other) {
            if (this != &other) {
                ptr = other.ptr;
                index = other.index;
            }
            return *this;
        }

        deque_iterator &operator=(deque_iterator &&other) noexcept {
            ptr = other.ptr;
            index = other.index;
            other.ptr = nullptr;
            return *this;
        }

        deque_iterator &operator+=(size_t n) {
            index += n;
            return *this;
        }

        deque_iterator &operator-=(size_t n) {
            index -= n;
            return *this;
        }

        deque_iterator operator+(size_t n) {
            auto it = *this;
            it.index += n;
            return it;
        }

        deque_iterator operator-(size_t n) {
            auto it = *this;
            it.index -= n;
            return it;
        }

        size_t operator-(const deque_iterator& n) {
            return index - n.index;
        }

        T& operator*() {
            return (*ptr)[index];
        }

        T* operator->() {
            return *ptr + index;
        }

        T* get() const {
            return *ptr + index;
        }
    };
private:
    T **base;
    size_t _size;
    size_t _capacity;
    Allocator alloc;
    size_t _begin;
    size_t _end;

    [[nodiscard]] size_t iaFromID(size_t id) const {
        return (id + _begin) % (_capacity * N);
    }

    [[nodiscard]] size_t ibFromIA(size_t ia) const {
        return ia / N;
    }

    [[nodiscard]] size_t icFromIA(size_t ia) const {
        return ia % N;
    }

public:
    deque();
    ~deque();
    deque(const deque &);
    deque(deque &&) noexcept;
    deque &operator=(const deque &);
    deque &operator=(deque &&) noexcept;
    void push_back(const T &);
    void push_front(const T &);
    void pop_back();
    void pop_front();
    T &operator[](size_t) const;
    [[nodiscard]] size_t size() const;
    [[nodiscard]] size_t capacity() const;
    deque_iterator begin() const;
    deque_iterator end() const;
    void clear();
    bool empty();
};

template<typename T, size_t N, class Allocator>
deque<T, N, Allocator> &deque<T, N, Allocator>::operator=(deque &&other) noexcept {
    clear();
    for (size_t i = 0; i < _capacity; ++i) {
        if (base[i]) {
            alloc.deallocate(base[i]);
        }
    }
    delete[] base;
    _capacity = other._capacity;
    _size = 0;
    _begin = 0;
    _end = 1;
    base = new T*[_capacity]{ nullptr };
    for (size_t i = 0; i < other._size; ++i) {
        push_back(other[i]);
    }
    other._begin = other._end = other._size = other._capacity = 0;
    other.base = nullptr;
}

template<typename T, size_t N, class Allocator>
deque<T, N, Allocator>::deque(deque &&other) noexcept {
    _capacity = other._capacity;
    _size = 0;
    _begin = 0;
    _end = 1;
    base = new T*[_capacity]{ nullptr };
    for (size_t i = 0; i < other._size; ++i) {
        push_back(other[i]);
    }
    other._begin = other._end = other._size = other._capacity = 0;
    other.base = nullptr;
}

template<typename T, size_t N, class Allocator>
deque<T, N, Allocator> &deque<T, N, Allocator>::operator=(const deque &other) {
    if (this != &other) {
        clear();
        for (size_t i = 0; i < _capacity; ++i) {
            if (base[i]) {
                alloc.deallocate(base[i]);
            }
        }
        delete[] base;
        _capacity = other._capacity;
        _size = 0;
        _begin = 0;
        _end = 1;
        base = new T*[_capacity]{ nullptr };
        for (size_t i = 0; i < other._size; ++i) {
            push_back(other[i]);
        }
    }
}

template<typename T, size_t N, class Allocator>
deque<T, N, Allocator>::deque(const deque &other) {
    _capacity = other._capacity;
    _size = 0;
    _begin = 0;
    _end = 1;
    base = new T*[_capacity]{ nullptr };
    for (size_t i = 0; i < other._size; ++i) {
        push_back(other[i]);
    }
}

template<typename T, size_t N, class Allocator>
deque<T, N, Allocator>::~deque() {
    clear();
    for (size_t i = 0; i < _capacity; ++i) {
        if (base[i]) {
            alloc.deallocate(base[i]);
        }
    }
    delete[] base;
}

template<typename T, size_t N, class Allocator>
bool deque<T, N, Allocator>::empty() {
    return !_size;
}

template<typename T, size_t N, class Allocator>
void deque<T, N, Allocator>::clear() {
    size_t oldSize = _size;
    for (size_t i = 0; i < oldSize; ++i) {
        deque::pop_back();
    }
}

template<typename T, size_t N, class Allocator>
typename deque<T, N, Allocator>::deque_iterator deque<T, N, Allocator>::end() const {
    return deque_iterator(this, _size);
}

template<typename T, size_t N, class Allocator>
typename deque<T, N, Allocator>::deque_iterator deque<T, N, Allocator>::begin() const {
    return deque_iterator(this, 0);
}

template<typename T, size_t N, class Allocator>
void deque<T, N, Allocator>::push_front(const T &value) {
    if (_begin) {
        --_begin;
    }
    else {
        _begin = _capacity * N - 1;
    }
    if ((ibFromIA(_begin) == ibFromIA(_end) && _size >= N - 1) || _size >= _capacity * N) {
        auto newBase = new T*[ _capacity * 2 ]{ nullptr };
        size_t count = 0;
        for (size_t i = ibFromIA(_begin); count < _capacity; ++i) {
            i %= _capacity;
            newBase[count] = base[i];
            count++;
        }
        delete[] base;
        base = newBase;
        _capacity *= 2;
        _begin = icFromIA(_begin);
        _end = iaFromID(_size);
    }
    if (!base[ibFromIA(_begin)]) {
        base[ibFromIA(_begin)] = alloc.allocate(N);
    }
    alloc.construct(base[ibFromIA(_begin)] + icFromIA(_begin), value);
    _size++;
}

template<typename T, size_t N, class Allocator>
void deque<T, N, Allocator>::pop_front() {
    if (_size) {
        alloc.destruct(base[ibFromIA(_begin)] + icFromIA(_begin));
        ++_begin;
        _size--;
        if (!_size) {
            _begin = 0;
        }
    }
}

template<typename T, size_t N, class Allocator>
void deque<T, N, Allocator>::pop_back() {
    if (_size) {
        alloc.destruct(base[ibFromIA(_end)] + icFromIA(_end) - 1);
        --_size;
        if (_end)
            --_end;
        else
            _end = _capacity * N - 1;
        if (!_size) {
            _end = 0;
        }
    }
}

template<typename T, size_t N, class Allocator>
size_t deque<T, N, Allocator>::capacity() const {
    return _capacity * N;
}

template<typename T, size_t N, class Allocator>
size_t deque<T, N, Allocator>::size() const {
    return _size;
}

template<typename T, size_t N, class Allocator>
T &deque<T, N, Allocator>::operator[](size_t index) const {
    return base[ibFromIA(iaFromID(index))][icFromIA(iaFromID(index))];
}

template<typename T, size_t N, class Allocator>
void deque<T, N, Allocator>::push_back(const T &value) {
    if ((_size >= _capacity * N) || ((ibFromIA(_end) == ibFromIA(_begin) && _size >= N - 1))) {
        auto newBase = new T*[ _capacity * 2 ]{ nullptr };
        size_t count = 0;
        for (size_t i = ibFromIA(_begin); count < _capacity; ++i) {
            i %= _capacity;
            newBase[count] = base[i];
            count++;
        }
        delete[] base;
        base = newBase;
        _capacity *= 2;
        _begin = icFromIA(_begin);
    }
    size_t ib = ibFromIA(iaFromID(_size));
    if (!base[ib]) {
        base[ib] = alloc.allocate(N);
    }
    alloc.construct(base[ib] + icFromIA(iaFromID(_size)), value);
    ++_size;
    _end = iaFromID(_size);
}

template<typename T, size_t N, class Allocator>
deque<T, N, Allocator>::deque() : _size(0), _capacity(N) {
    _begin = 0;
    _end = 1;
    base = new T *[N] { nullptr };
    base[0] = alloc.allocate(N);
}


#endif//DEQUE_H
