#include <iostream>

void *memcpy(void *dest, const void *src, size_t count) {
    auto _dest = (char*)dest;
    auto _src = (const char*)src;
    for (int i = 0; i < count; ++i) {
        _dest[i] = _src[i];
    }
    return _dest;
}
