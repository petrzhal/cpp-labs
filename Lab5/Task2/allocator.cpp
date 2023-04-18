#include <iostream>

template<typename T>
class allocator {
    static_assert(!std::is_same_v<T, void>, "Type of the allocator can not be void");
public:
    using pointer = T*;

    allocator() = default;

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
