#ifndef QUEUE_SHARED_H
#define QUEUE_SHARED_H

#include <iostream>

namespace ptr {
    template<typename T>
    class shared_ptr {
    private:
        T *ptr = nullptr;
        size_t *counter = nullptr;
        void _clean();
    public:
        shared_ptr() : ptr(nullptr), counter(nullptr) {};
        shared_ptr(T *ptr) : ptr(ptr), counter(new size_t(1)) {};
        shared_ptr(const shared_ptr &other);
        shared_ptr &operator=(const shared_ptr &other);
        shared_ptr(shared_ptr &&other) noexcept;
        shared_ptr &operator=(shared_ptr &&other) noexcept;
        [[nodiscard]] size_t use_count() const;
        T *get() const;
        T &operator*();
        T *operator->();
        ~shared_ptr();
    };

    template<typename T>
    shared_ptr<T>::~shared_ptr() {
        _clean();
    }

    template<typename T>
    T *shared_ptr<T>::operator->() {
        return ptr;
    }

    template<typename T>
    T &shared_ptr<T>::operator*() {
        return *ptr;
    }

    template<typename T>
    T *shared_ptr<T>::get() const {
        return ptr;
    }

    template<typename T>
    size_t shared_ptr<T>::use_count() const {
        return *counter;
    }

    template<typename T>
    shared_ptr<T> &shared_ptr<T>::operator=(shared_ptr &&other) noexcept {
        shared_ptr::_clean();
        ptr = other.ptr;
        counter = other.counter;
        other.ptr = nullptr;
        other.counter = nullptr;
        return *this;
    }

    template<typename T>
    shared_ptr<T>::shared_ptr(shared_ptr &&other) noexcept {
        ptr = other.ptr;
        counter = other.counter;
        other.ptr = nullptr;
        other.counter = nullptr;
    }

    template<typename T>
    shared_ptr<T> &shared_ptr<T>::operator=(const shared_ptr &other) {
        if (this != &other) {
            _clean();
            ptr = other.ptr;
            counter = other.counter;
            if (other.ptr != nullptr)
                (*counter)++;
        }
        return *this;
    }

    template<typename T>
    void shared_ptr<T>::_clean() {
        if (counter == nullptr) {
            return;
        }
        if (--(*counter) == 0) {
            delete ptr;
            delete counter;
        }
    }

    template <typename T>
    shared_ptr<T>::shared_ptr(const shared_ptr& other) {
        ptr = other.ptr;
        counter = other.counter;
        if (other.ptr != nullptr)
            (*counter)++;
    }

    template <typename T, typename... Args>
    shared_ptr<T> make_shared(Args&&... args) {
        auto ptr = new T(std::forward<Args>(args)...);
        return shared_ptr<T>(ptr);
    }
}

#endif//QUEUE_SHARED_H
