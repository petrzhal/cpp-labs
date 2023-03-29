#include <iostream>
#include "shared.cpp"
#include "unique.cpp"
#include "move.cpp"
#include "string.cpp"
#include "cfunc.cpp"

void *memcpy(void *dest, const void *src, size_t count) {
    auto _dest = (char*)dest;
    auto _src = (const char*)src;
    for (int i = 0; i < count; ++i) {
        _dest[i] = _src[i];
    }
    return _dest;
}

void* memmove(void* dest, const void* src, std::size_t count) {

}

int main() {
    char source[] = "kal", dest[4];
    memcpy(dest, source, 4);
    std::cout << dest;
}
