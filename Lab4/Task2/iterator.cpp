#include <iostream>

template<class T>
class iterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = T;
    using pointer           = value_type*;
    using reference         = value_type&;
private:
    pointer current;
public:
    iterator() {
        current = nullptr;
    }

    iterator(const iterator& other) {
        this->current = other.current;
    }

    iterator(iterator&& other) noexcept {
        current = other.current;
        other.current = nullptr;
    }

    explicit iterator(pointer iter) {
        current = iter;
    }

    iterator& operator++() {
        current++;
        return *this;
    }

    iterator& operator--() {
        current--;
        return *this;
    }

    iterator operator++(int) {
        iterator old = *this;
        current++;
        return old;
    }

    iterator operator--(int) {
        iterator old = *this;
        current--;
        return old;
    }

    bool operator<(iterator other) {
        return this->current < other.current;
    }

    bool operator>(iterator other) {
        return this->current > other.current;
    }

    virtual bool operator!=(iterator other) {
        return this->current != other.current;
    }

    bool operator==(iterator other) {
        return this->current == other.current;
    }

    iterator& operator=(const iterator &other) {
        current = other.current;
        return *this;
    }

    iterator& operator=(iterator&& other) noexcept {
        current = other->current;
        other.current = nullptr;
        return *this;
    }

    iterator& operator+=(size_t n) {
        current += n;
        return *this;
    }

    iterator& operator-=(size_t n) {
        current -= n;
        return *this;
    }

    iterator operator+(size_t n) {
        return iterator(current + n);
    }

    iterator operator-(size_t n) {
        return iterator(current - n);
    }

    size_t operator-(iterator n) {
        return current - n.current;
    }

    reference operator*() {
        return *current;
    }

    pointer operator->() {
        return current;
    }

    pointer get() const {
        return current;
    }
};

template<class T>
class reverse_iterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = T;
    using pointer           = T*;
    using reference         = T&;
private:
    pointer current;
public:
    reverse_iterator() {
        current = nullptr;
    }

    reverse_iterator(const reverse_iterator& other) {
        this->current = other.current;
    }

    reverse_iterator(reverse_iterator&& other) noexcept {
        current = other.current;
        other.current = nullptr;
    }

    explicit reverse_iterator(pointer iter) {
        current = iter;
    }

    reverse_iterator& operator++() {
        current--;
        return *this;
    }

    reverse_iterator& operator--() {
        current++;
        return *this;
    }

    reverse_iterator operator++(int) {
        reverse_iterator old = *this;
        current--;
        return old;
    }

    reverse_iterator operator--(int) {
        reverse_iterator old = *this;
        current++;
        return old;
    }

    pointer operator->() {
        return current;
    }

    virtual bool operator!=(reverse_iterator other) {
        return this->current != other.current;
    }

    bool operator==(reverse_iterator other) {
        return this->current == other.current;
    }

    reverse_iterator& operator=(const reverse_iterator &other) {
        current = other.current;
        return *this;
    }

    reverse_iterator& operator=(reverse_iterator&& other) noexcept {
        current = other->current;
        other.current = nullptr;
        return *this;
    }

    reverse_iterator operator-(size_t n) {
        return reverse_iterator(current + n);
    }

    reverse_iterator operator+(size_t n) {
        return reverse_iterator(current - n);
    }

    reverse_iterator& operator+=(size_t n) {
        current -= n;
        return *this;
    }

    reverse_iterator& operator-=(size_t n) {
        current += n;
        return *this;
    }

    size_t operator-(reverse_iterator n) {
        return current - n.current;
    }

    reference operator*() {
        return *current;
    }

    pointer get() const {
        return current;
    }
};

template<class T>
class const_iterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = T;
    using pointer           = const value_type*;
    using reference         = value_type&;
private:
    pointer current;
public:
    const_iterator() {
        current = nullptr;
    }

    const_iterator(const const_iterator& other) {
        this->current = other.current;
    }

    const_iterator(const_iterator&& other) noexcept {
        current = other.current;
        other.current = nullptr;
    }

    explicit const_iterator(pointer iter) {
        current = iter;
    }

    const_iterator& operator++() {
        current++;
        return *this;
    }

    const_iterator& operator--() {
        current--;
        return *this;
    }

    const_iterator operator++(int) {
        iterator old = *this;
        current++;
        return old;
    }

    const_iterator operator--(int) {
        iterator old = *this;
        current--;
        return old;
    }

    bool operator<(const_iterator other) {
        return this->current < other.current;
    }

    bool operator>(const_iterator other) {
        return this->current > other.current;
    }

    virtual bool operator!=(const_iterator other) {
        return this->current != other.current;
    }

    bool operator==(const_iterator other) {
        return this->current == other.current;
    }

    const_iterator& operator=(const const_iterator &other) {
        current = other.current;
        return *this;
    }

    const_iterator& operator=(const_iterator&& other) noexcept {
        current = other->current;
        other.current = nullptr;
        return *this;
    }

    const_iterator& operator+=(size_t n) {
        current += n;
        return *this;
    }

    const_iterator& operator-=(size_t n) {
        current -= n;
        return *this;
    }

    const_iterator operator+(size_t n) {
        return iterator(current + n);
    }

    const_iterator operator-(size_t n) {
        return iterator(current - n);
    }

    size_t operator-(const_iterator n) {
        return current - n.current;
    }

    reference operator*() {
        return *current;
    }

    pointer operator->() {
        return current;
    }

    pointer get() const {
        return current;
    }
};