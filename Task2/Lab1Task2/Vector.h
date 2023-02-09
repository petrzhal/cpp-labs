#ifndef DATA_VECTOR_H
#define DATA_VECTOR_H

#include <iostream>

template<typename T>
class Vector {
public:
    Vector() {
        arr_ = new T[1];
        capacity_ = 1;
    }
    Vector(Vector& other) {
        if (this != &other) {
            delete[] arr_;
            arr_ = other.arr_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.arr_ = nullptr;
            other.size_ = other.capacity_ = 0;
        }
    }
    Vector(Vector&& other)  noexcept {
        if (this != &other) {
            delete[] arr_;
            arr_ = other.arr_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.arr_ = nullptr;
            other.size_ = other.capacity_ = 0;
        }
    }
    Vector& operator=(Vector& other) {
        if (this != &other) {
            delete[] arr_;
            arr_ = other.arr_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.arr_ = nullptr;
            other.size_ = other.capacity_ = 0;
        }
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] arr_;
            arr_ = other.arr_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.arr_ = nullptr;
            other.size_ = other.capacity_ = 0;
        }
        return *this;
    }

    ~Vector() {
        delete[] arr_;
    }
public:
    [[nodiscard]] bool isEmpty() const {
        return size_ == 0;
    }

    [[nodiscard]] size_t size() const {
        return size_;
    }

    [[nodiscard]] size_t capacity() const {
        return capacity_;
    }

    void push_back(T& value) {
        if (size_ >= capacity_) addMemory();
        arr_[size_++] = value;
    }

    void remove(size_t index) {
        for (size_t i = index + 1; i < size_; ++i) {
            arr_[i - 1] = arr_[i];
        }
        --size_;
    }
public:
    T* begin() {
        return &arr_[0];
    }

    const T* begin() const {
        return &arr_[0];
    }

    T* end() {
        return &arr_[size_];
    }

    const T* end() const {
        return &arr_[size_];
    }
public:
    T& operator[](size_t index)  {
        return arr_[index];
    }

    const T& operator[](size_t index) const {
        return arr_[index];
    }
private:

    void addMemory() {
        capacity_ *= 2;
        T* tmp = arr_;
        arr_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) arr_[i] = tmp[i];
        delete[] tmp;
    }

    T* arr_;
    size_t size_{};
    size_t capacity_{};
};

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const Vector<T>& vec) {
    for (const T& val : vec) os << val << " ";
    return os;
}

#endif
