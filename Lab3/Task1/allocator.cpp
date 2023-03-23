#include <iostream>

template<typename T>
class allocator {
public:
    using pointer = T*;

    [[nodiscard]] pointer allocate(size_t n) const {
        return static_cast<pointer>(::operator new(n * sizeof(T)));
    }

    template<typename... Args>
    void construct(pointer ptr, Args&&... args) const {
        new (ptr) T(args...);
    }

    void deallocate(pointer ptr, size_t = size_t()) const {
        ::operator delete(ptr);
    }

    void destruct(pointer ptr) const {
        ptr->~T();
    }
};
