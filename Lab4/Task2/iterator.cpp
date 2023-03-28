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

    iterator& operator=(const iterator *other) {
        current = other->current;
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

    pointer get_pointer() const {
        return current;
    }
};