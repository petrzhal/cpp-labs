#include <iostream>

template<typename T>
class shared_ptr {
private:
    T *ptr = nullptr;
    size_t *counter = nullptr;

    void _clean() {
        if (--(*counter) == 0) {
            delete ptr;
            delete counter;
        }
    }
public:
    shared_ptr() : ptr(nullptr), counter(nullptr) {};
    explicit shared_ptr(T *ptr) : ptr(ptr), counter(new size_t(1)){};
    shared_ptr(const shared_ptr &other) {
        ptr = other.ptr;
        counter = other.counter;
        if (other.ptr != nullptr)
            (*counter)++;
    }
    shared_ptr &operator=(const shared_ptr &other) {
        if (this != other) {
            ptr = other.ptr;
            counter = other.counter;
            if (other.ptr != nullptr)
                (*counter)++;
        }
    }
    shared_ptr(shared_ptr &&other) noexcept {
        ptr = other.ptr;
        counter = other.counter;
        other.ptr = other.counter = nullptr;
    }
    shared_ptr &operator=(shared_ptr &&other) noexcept {
        shared_ptr::_clean();
        ptr = other.ptr;
        counter = other.counter;
        other.ptr = other.counter = nullptr;
    }
    [[nodiscard]] size_t use_count() const {
        return *counter;
    }
    T *get() const {
        return ptr;
    }
    T &operator*() {
        return *ptr;
    }
    T *operator->() {
        return ptr;
    }
    ~shared_ptr() {
        _clean();
    }
};

template <typename T>
shared_ptr<T> make_shared(T* ptr) {
    return shared_ptr<T>(ptr);
}