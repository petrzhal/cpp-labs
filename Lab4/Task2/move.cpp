#include <iostream>

namespace mv {
    template<typename T>
    std::remove_reference_t<T> &&move(T &&x) noexcept {
        return static_cast<std::remove_reference_t<T> &&>(x);
    }
}