#include <memory>

template <typename T, typename Deleter = std::default_delete<T>>
class unique_ptr {
private:
    T* ptr = nullptr;
public:
    unique_ptr() : ptr(nullptr) {}
    explicit unique_ptr(T* ptr) : ptr(ptr) {}
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr(unique_ptr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }
    unique_ptr& operator=(unique_ptr&& other) noexcept {
        ptr = other.ptr;
        other.ptr= nullptr;
        return *this;
    }
    T& operator*() {
        return *ptr;
    }
    T* get() const {
        return ptr;
    }
    T* operator->() {
        return ptr;
    }
    ~unique_ptr() {
        Deleter()(ptr);
    }
};

template <typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... args) {
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
}