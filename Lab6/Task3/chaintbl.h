#ifndef HASH_TBL_H
#define HASH_TBL_H
#include "stack.h"
#include <iostream>

template<typename Key, typename Value, size_t K = 2048>
class HTable {
protected:
    stack<std::pair<Key, Value>> *base;
    size_t _size;

    size_t hash(const Key &);
    bool contains(stack<std::pair<Key, Value>> &, const Key &);
    void replace(stack<std::pair<Key, Value>> &, const Key &, const Value &);
    Value &get(stack<std::pair<Key, Value>> &, const Key &);
    void erase(stack<std::pair<Key, Value>> &, const Key &);

public:
    HTable()
        : base(new stack<std::pair<Key, Value>>[K]{}),
          _size(0) {}
    ~HTable();
    HTable(const HTable &);
    HTable(HTable &&) noexcept;
    void clear();
    HTable &operator=(const HTable &);
    HTable &operator=(HTable &&) noexcept;
    void insert(const Key &, const Value &);
    void erase(const Key &);
    Value &operator[](const Key &);
    bool contains(const Key &);
    [[nodiscard]] size_t size() const;
};

template<typename Key, typename Value, size_t K>
bool HTable<Key, Value, K>::contains(stack<std::pair<Key, Value>> &st, const Key &key) {
    stack<std::pair<Key, Value>> tmp;
    while (!st.empty()) {
        if (st.top().first == key) {
            while (!tmp.empty()) {
                st.push(tmp.pop());
            }
            return true;
        }
        tmp.push(st.pop());
    }
    while (!tmp.empty()) {
        st.push(tmp.pop());
    }
    return false;
}

template<typename Key, typename Value, size_t K>
void HTable<Key, Value, K>::replace(stack<std::pair<Key, Value>> &st, const Key &key, const Value &value) {
    stack<std::pair<Key, Value>> tmp;
    while (!st.empty()) {
        if (st.top().first == key) {
            st.top().second = value;
            while (!tmp.empty()) {
                st.push(tmp.pop());
            }
            return;
        }
        tmp.push(st.pop());
    }
    while (!tmp.empty()) {
        st.push(tmp.pop());
    }
}

template<typename Key, typename Value, size_t K>
Value &HTable<Key, Value, K>::get(stack<std::pair<Key, Value>> &st, const Key &key) {
    stack<std::pair<Key, Value>> tmp;
    while (!st.empty()) {
        if (st.top().first == key) {
            auto& r = st.top().second;
            while (!tmp.empty()) {
                st.push(tmp.pop());
            }
            return r;
        }
        tmp.push(st.pop());
    }
    while (!tmp.empty()) {
        st.push(tmp.pop());
    }
    st.push(std::make_pair(key, Value()));
    return st.top().second;
}

template<typename Key, typename Value, size_t K>
void HTable<Key, Value, K>::erase(stack<std::pair<Key, Value>> &st, const Key &key) {
    stack<std::pair<Key, Value>> tmp;
    while (!st.empty()) {
        if (st.top().first == key) {
            st.pop();
            break;
        }
        tmp.push(st.pop());
    }
    while (!tmp.empty()) {
        st.push(tmp.pop());
    }
}

template<typename Key, typename Value, size_t K>
HTable<Key, Value, K>::~HTable() {
    delete[] base;
}

template<typename Key, typename Value, size_t K>
HTable<Key, Value, K> &HTable<Key, Value, K>::operator=(HTable &&other) noexcept {
    delete[] base;
    base = other.base;
    _size = other._size;
    other.base = nullptr;
    other._size = 0;
}

template<typename Key, typename Value, size_t K>
HTable<Key, Value, K>::HTable(HTable &&other) noexcept {
    base = other.base;
    _size = other._size;
    other.base = nullptr;
    other._size = 0;
}

template<typename Key, typename Value, size_t K>
void HTable<Key, Value, K>::clear() {
    for (size_t i = 0; i < K; ++i) {
        base[i].clear();
    }
    _size = 0;
}

template<typename Key, typename Value, size_t K>
HTable<Key, Value, K> &HTable<Key, Value, K>::operator=(const HTable &other) {
    if (this != &other) {
        delete[] base;
        base = reinterpret_cast<stack<std::pair<Key, Value>>*>(new int8_t*[K * sizeof(stack<std::pair<Key, Value>>) * other._size]);
        for (size_t i = 0; i < other._size; ++i) {
            new (base + i) stack<std::pair<Key, Value>>(other.base[i]);
        }
        _size = other._size;
    }
    return *this;
}

template<typename Key, typename Value, size_t K>
HTable<Key, Value, K>::HTable(const HTable &other) {
     base = reinterpret_cast<stack<std::pair<Key, Value>>*>(new int8_t*[K * sizeof(stack<std::pair<Key, Value>>) * other._size]);
     for (size_t i = 0; i < other._size; ++i) {
        new (base + i) stack<std::pair<Key, Value>>(other.base[i]);
     }
     _size = other._size;
}

template<typename Key, typename Value, size_t K>
bool HTable<Key, Value, K>::contains(const Key &key) {
    return contains(base[hash(key)], key);
}

template<typename Key, typename Value, size_t K>
void HTable<Key, Value, K>::erase(const Key &key) {
    erase(base[hash(key)], key);
}

template<typename Key, typename Value, size_t K>
size_t HTable<Key, Value, K>::size() const {
    return _size;
}

template<typename Key, typename Value, size_t K>
Value &HTable<Key, Value, K>::operator[](const Key &key) {
    return get(base[hash(key)], key);
}

template<typename Key, typename Value, size_t K>
void HTable<Key, Value, K>::insert(const Key &key, const Value &value) {
    size_t i = hash(key);
    if (contains(base[i], key)) {
        replace(base[i], key, value);
    } else {
        base[i].push(std::make_pair(key, value));
        ++_size;
    }
}

template<typename Key, typename Value, size_t K>
size_t HTable<Key, Value, K>::hash(const Key &key) {
    return static_cast<size_t>(key * 13 / 3) % K;
}

#endif//HASH_TBL_H
