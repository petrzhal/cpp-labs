#include <bits/stdc++.h>

inline void *my_memcpy(void *dest, const void *src, size_t count) {
    auto _dest = (unsigned char *)dest;
    auto _src = (const unsigned char *)src;
    for (int i = 0; i < count; ++i) {
        _dest[i] = _src[i];
    }
    return _dest;
}

inline size_t my_strlen(const char *str) {
    size_t size = 0;
    while (str[size] != '\0') ++size;
    return size;
}

inline void *my_memmove(void *dest, const void *src, std::size_t count) {
    void *ret = dest;
    if (dest <= src || (char *) dest >= ((char *) src + count)) {
        while (count--) {
            *(char *) dest = *(char *) src;
            dest = (char *) dest + 1;
            src = (char *) src + 1;
        }
    } else {
        dest = (char *) dest + count - 1;
        src = (char *) src + count - 1;
        while (count--) {
            *(char *) dest = *(char *) src;
            dest = (char *) dest - 1;
            src = (char *) src - 1;
        }
    }
    return (ret);
}

inline char *my_strcpy(char *str1, const char *str2) {
    size_t length = strlen(str2);
    for (int i = 0; i < length; ++i) {
        str1[i] = str2[i];
    }
    str1[length] = '\0';
    return str1;
}

inline char *my_strncpy(char *str1, const char *str2) {
    size_t length = strlen(str2);
    int c = 0;
    for (int i = 0; i < length && str2[i] != '\0'; ++i) {
        str1[i] = str2[i];
        c++;
    }
    str1[c] = '\0';
    return str1;
}

inline char *my_strcat(char *dest, const char *src) {
    size_t len1 = strlen(dest);
    size_t len2 = strlen(src);
    int c = 0;
    for (size_t i = len1; i < len2 + len1; ++i) {
        dest[i] = src[c++];
    }
    dest[len1 + len2] = '\0';
    return dest;
}

inline char *my_strncat(char *dest, const char *src) {
    size_t len1 = strlen(dest);
    size_t len2 = strlen(src);
    int c = 0;
    for (size_t i = len1; i < len2 + len1 && src[c] != '\0'; ++i) {
        dest[i] = src[c++];
    }
    dest[len1 + len2] = '\0';
    return dest;
}

inline int my_memcmp(const void *s1, const void *s2, int len) {
    auto *p = (unsigned char *) s1;
    auto *q = (unsigned char *) s2;
    int charCompareStatus = 0;
    if (s1 == s2) {
        return charCompareStatus;
    }
    while (len > 0) {
        if (*p != *q) {
            charCompareStatus = (*p > *q) ? 1 : -1;
            break;
        }
        len--;
        p++;
        q++;
    }
    return charCompareStatus;
}

inline int my_strcmp(const char *X, const char *Y) {
    char srtсmp[strlen(Y)];
    while (*X) {
        if (*X != *Y) {
            break;
        }
        X++;
        Y++;
    }
    return strcmp(X, Y)/**(const unsigned char*)X - *(const unsigned char*)Y*/;
}

inline char *my_strcoll(char *X, const char *Y) {
    char srtcoll[strlen(Y)];
    return strcpy(X, Y);
}

inline int my_strncmp(const char *X, const char *Y, int n) {
    char srtсmp[strlen(Y)];
    while (*X) {
        if (*X != *Y) {
            break;
        }
        X++;
        Y++;
    }
    return strcmp(X, Y)/**(const unsigned char*)X - *(const unsigned char*)Y*/;
}

inline size_t my_strxfrm(char* s1, const char* s2, size_t n) {
    char srtсmp[strlen(s1)];
    while (*s1) {
        if (*s1 != *s2) {
            break;
        }
        s1++;
        s2++;
    }
    return strxfrm(s1, s2, 3);
}

inline const char* my_strtok(char* s, char d) {
    static char* input = NULL;
    if (s != NULL)
        input = s;
    if (input == NULL)
        return NULL;
    char* result = new char[strlen(input) + 1];
    int i = 0;
    for (; input[i] != '\0'; i++) {
        if (input[i] != d)
            result[i] = input[i];
        else {
            result[i] = '\0';
            input = input + i + 1;
            return result;
        }
    }
    result[i] = '\0';
    input = NULL;
    return result;
}

inline void *my_memset(void *b, char c, int len) {
    int i = 0;
    unsigned char *p = (unsigned char*)b;
    while(len > 0) {
        *p = c;
        p++;
        len--;
    }
    return b;
}

inline const char *my_strerror(int er) {
    switch (er) {
    case 0:
        return "No child processes";
    case 1:
        return "Operation not permitted";
    case 2:
        return "No such file or directory";
    case 3:
        return "No such process";
    case 4:
        return "Interrupted function call";
    case 5:
        return "Input/output error";
    case 6:
        return "No such device or address";
    case 7:
        return "Arg list too long";
    case 8:
        return "Exec format error";
    case 9:
        return "Bad file descriptor";
    case 10:
        return "Resource temporarily";
    case 11:
        return "unavailable";
    case 12:
        return "Not enough space";
    case 13:
        return "Permission denied";
    case 14:
        return "Bad address";
    case 15:
        return "Unknown error";
    case 16:
        return "No error";
    case 17:
        return "File exists";
    case 18:
        return "Improper link";
    case 19:
        return "No such device";
    case 20:
        return "Not a directory";
    case 21:
        return "Is a directory";
    case 22:
        return "File too large";
    case 23:
        return "Too many open files in system";
    case 24:
        return "Too many open files";
    case 25:
        return "Inappropriate I/O control operation";
    case 26:
        return "Unknown error";
    case 27:
        return "File too large";
    case 28:
        return "No space left on device";
    case 29:
        return "Invalid seek";
    case 30:
        return "Read-only file system";
    case 31:
        return "Too many links";
    case 32:
        return "Broken pipe";
    case 33:
        return "Domain error";
    case 34:
        return "Result too large";
    case 35:
        return "Unknown error";
    case 36:
        return "Resource deadlock avoided";
    case 37:
        return "Unknown error";
    case 38:
        return "Filename too long";
    default:
        return strerror(er);
    }
}
