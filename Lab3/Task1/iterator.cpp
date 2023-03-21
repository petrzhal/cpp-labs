#include <iostream>
namespace it {
    template<class T>
    class const_iterator {
    private:
        const T* it;
    public:
        const_iterator() {
            it = nullptr;
        }

        const_iterator(const const_iterator<T>& other) {
            this->it = other.it;
        }

        explicit const_iterator(T *iter) {
            it = iter;
        }

        const T *operator->() {
            return it;
        }

        bool operator!=(const const_iterator &other) {
            return it != other.it;
        }

        const_iterator& operator=(const const_iterator &other) {
            it = other.it;
            return *this;
        }

        const T &operator*() {
            return *it;
        }
        const T* get_pointer() {
            return it;
        }
    };

    template<class T>
    class iterator {
    private:
        T *it;
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = T*;
        using reference         = T&;

        iterator() {
            it = nullptr;
        }

        iterator(const iterator& other) {
            this->it = other.it;
        }

        explicit iterator(T *iter) {
            it = iter;
        }

        iterator& operator++() {
            it++;
            return *this;
        }

        iterator& operator--() {
            it--;
            return *this;
        }

        iterator& operator++(int) {
            it++;
            return *this;
        }

        iterator& operator--(int) {
            it--;
            return *this;
        }

        pointer operator->() {
            return it;
        }

        bool operator<(iterator other) {
            return this->it < other.it;
        }

        bool operator>(iterator other) {
            return this->it > other.it;
        }

        virtual bool operator!=(iterator other) {
            return this->it != other.it;
        }

        bool operator==(iterator other) {
            return this->it == other.it;
        }

        iterator& operator=(const iterator &other) {
            it = other.it;
            return *this;
        }

        iterator& operator=(const iterator *other) {
            it = other->it;
            return *this;
        }

        iterator operator+(size_t n) {
            return iterator(it + n);
        }

        iterator operator-(size_t n) {
            return iterator(it - n);
        }

        size_t operator-(iterator n) {
            return it - n.it;
        }

        reference operator*() {
            return *it;
        }

        pointer get_pointer() const {
            return it;
        }
    };

    template<class T>
    class reverse_iterator {
    protected:
        T *it;
    public:
        reverse_iterator() {
            it = nullptr;
        }

        explicit reverse_iterator(const iterator<T>& other) {
            this->it = other.it;
        }

        explicit reverse_iterator(T *iter) {
            it = iter;
        }

        reverse_iterator<T>& operator++() {
            it--;
            return *this;
        }

        reverse_iterator<T>& operator--() {
            it++;
            return *this;
        }

        reverse_iterator<T>& operator++(int) {
            it--;
            return *this;
        }

        reverse_iterator<T>& operator--(int) {
            it++;
            return *this;
        }

        T *operator->() {
            return it;
        }

        virtual bool operator!=(reverse_iterator other) {
            return this->it != other.it;
        }

        bool operator==(reverse_iterator other) {
            return this->it == other.it;
        }

        reverse_iterator& operator=(const reverse_iterator &other) {
            it = other.it;
            return *this;
        }

        reverse_iterator& operator=(const reverse_iterator *other) {
            it = other->it;
            return *this;
        }

        reverse_iterator operator-(size_t n) {
            return reverse_iterator(it + n);
        }

        reverse_iterator operator+(size_t n) {
            return reverse_iterator(it - n);
        }

        size_t operator-(reverse_iterator n) {
            return it - n.it;
        }

        T &operator*() {
            return *it;
        }

        T* get_pointer() const {
            return it;
        }
    };
};
