#include <iostream>

template<typename T>
class shared_ptr;

template <typename T, typename... Args>
shared_ptr<T> make_shared(Args&&... args);

template <typename T>
class weak_ptr {
    template <typename U>
    friend class shared_ptr;
private:

    T* ptr;
    size_t* counter;

public:
    weak_ptr()
        : ptr(nullptr),
        counter(nullptr) {}
    weak_ptr(const shared_ptr<T>&);
    weak_ptr(const weak_ptr& ptr)
        : ptr(ptr.ptr),
        counter(ptr.counter) {}
    weak_ptr& operator=(const shared_ptr<T>&);
    weak_ptr& operator=(const weak_ptr&);
    shared_ptr<T> lock();
};

template<typename T>
weak_ptr<T>& weak_ptr<T>::operator=(const weak_ptr& other) {
    if (this != &other) {
        ptr = other.ptr;
        counter = other.counter;
    }
    return *this;
}

template <typename T>
shared_ptr<T> weak_ptr<T>::lock() {
    if (ptr && counter && *counter > 0) {
        ++(*counter);
        return shared_ptr<T>(ptr, counter);
    }
    return shared_ptr<T>(nullptr, nullptr);
}

template <typename T>
weak_ptr<T>::weak_ptr(const shared_ptr<T>& ptr) {
    this->ptr = ptr.ptr;
    counter = ptr.counter;
}

template <typename T>
weak_ptr<T>& weak_ptr<T>::operator=(const shared_ptr<T>& ptr)
{
    if (*counter) {
        (*counter)--;
    }
    else {
        delete this->ptr;
        this->ptr = nullptr;
        delete counter;
        counter = nullptr;
    }
    this->ptr = ptr.ptr;
    counter = ptr.counter;
    return *this;
}


template<typename T>
class shared_ptr {
private:
    T* ptr;
    size_t* counter;
    void _clean();
public:
    shared_ptr()
        : ptr(nullptr),
        counter(nullptr) {}
    explicit shared_ptr(T* ptr)
        : ptr(ptr),
        counter(new size_t(1)) {}
    shared_ptr(T* ptr, size_t* counter)
        : ptr(ptr),
        counter(counter) {}
    shared_ptr(const shared_ptr& other);
    shared_ptr& operator=(const shared_ptr& other);
    shared_ptr(shared_ptr&& other) noexcept;
    shared_ptr& operator=(shared_ptr&& other) noexcept;
    shared_ptr& operator=(std::nullptr_t p) {
        ptr = p;
        counter = nullptr;
        return *this;
    }
    bool operator==(const shared_ptr& other) {
        return ptr == other.ptr;
    }
    bool operator!() {
        return !ptr;
    }
    [[nodiscard]] size_t use_count() const;
    T* get() const;
    T& operator*();
    T* operator->();
    ~shared_ptr();
    void reset() noexcept;
    template <typename U>
    friend class weak_ptr;
};

template<typename T>
void shared_ptr<T>::reset() noexcept {
    if (!counter)
        return;
    if (*counter) {
        --(*counter);
    }
    if (!(*counter)) {
        delete ptr;
        delete counter;
        counter = nullptr;
        ptr = nullptr;
    }
}

template<typename T>
shared_ptr<T>::~shared_ptr() {
    this->_clean();
}

template<typename T>
T* shared_ptr<T>::operator->() {
    return ptr;
}

template<typename T>
T& shared_ptr<T>::operator*() {
    return *ptr;
}

template<typename T>
T* shared_ptr<T>::get() const {
    return ptr;
}

template<typename T>
size_t shared_ptr<T>::use_count() const {
    return *counter;
}

template<typename T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr&& other) noexcept {
    this->_clean();
    ptr = other.ptr;
    counter = other.counter;
    other.ptr = nullptr;
    other.counter = nullptr;
    return *this;
}

template<typename T>
shared_ptr<T>::shared_ptr(shared_ptr&& other) noexcept {
    ptr = other.ptr;
    counter = other.counter;
    other.ptr = nullptr;
    other.counter = nullptr;
}

template<typename T>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr& other) {
    if (this != &other) {
        ptr = other.ptr;
        counter = other.counter;
        if (other.ptr)
            (*counter)++;
    }
    return *this;
}

template<typename T>
void shared_ptr<T>::_clean() {
    if (!counter || !ptr)
        return;
    if (--(*counter) == 0) {
        delete ptr;
        ptr = nullptr;
        delete counter;
        counter = nullptr;
    }
}

template <typename T>
shared_ptr<T>::shared_ptr(const shared_ptr& other) {
    ptr = other.ptr;
    counter = other.counter;
    if (other.ptr && other.counter)
        (*other.counter)++;
}

template <typename T, typename... Args>
shared_ptr<T> make_shared(Args&&... args) {
    return shared_ptr<T>(new T(std::forward<Args>(args)...));
}
