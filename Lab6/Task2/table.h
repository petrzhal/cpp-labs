#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <cmath>
#include <iostream>

template<typename Key, typename Value>
struct Node {
    Key key;
    Value value;
    bool isUsed;
    Node()
        : key(Key()),
          value(Value()),
          isUsed(false) {}
    Node(const Node &other) {
        key = other.key;
        value = other.value;
        isUsed = other.isUsed;
    }
    Node(const Key &key, const Value &value)
        : key(key),
          value(value),
          isUsed(true) {}
};

template<typename Key, typename Value, size_t K = 2048>
class HashTable {
private:
    Node<const Key, Value> *base;
    size_t _size;
    size_t hash(const Key &);

public:
    HashTable()
        : _size(0),
          base(new Node<const Key, Value>[K] {}) {}
    HashTable(const HashTable &);
    HashTable(HashTable &&) noexcept;
    HashTable &operator=(const HashTable &);
    HashTable &operator=(HashTable &&) noexcept;
    void insert(const Key &, const Value &);
    void erase(const Key &);
    Value &operator[](const Key &);
    bool contains(const Key &);
    void clear();
};

template<typename Key, typename Value, size_t K>
HashTable<Key, Value, K> &HashTable<Key, Value, K>::operator=(HashTable &&other) noexcept {
    delete[] base;
    base = other.base;
    _size = other._size;
}

template<typename Key, typename Value, size_t K>
HashTable<Key, Value, K>::HashTable(HashTable &&other) noexcept {
    base = other.base;
    _size = other._size;
}

template<typename Key, typename Value, size_t K>
HashTable<Key, Value, K> &HashTable<Key, Value, K>::operator=(const HashTable &other) {
    if (this != &other) {
        delete[] base;
        base = reinterpret_cast<Node<const Key, Value>>(new int8_t[sizeof(Node<const Key, Value>) * K]{});
        for (size_t i = 0; i < K; ++i) {
            new (base + i) Node<const Key, Value>(other.base[i]);
        }
        _size = other._size;
    }
    return *this;
}

template<typename Key, typename Value, size_t K>
HashTable<Key, Value, K>::HashTable(const HashTable &other) {
    base = reinterpret_cast<Node<const Key, Value>>(new int8_t[sizeof(Node<const Key, Value>) * K]{});
    for (size_t i = 0; i < K; ++i) {
        new (base + i) Node<const Key, Value>(other.base[i]);
    }
    _size = other._size;
}

template<typename Key, typename Value, size_t K>
void HashTable<Key, Value, K>::clear() {
    for (size_t i = 0; i < K; ++i) {
        if (base[i].isUsed) {
            _size--;
        }
    }
}

template<typename Key, typename Value, size_t K>
bool HashTable<Key, Value, K>::contains(const Key &key) {
    size_t i = hash(key);
    size_t j = i;
    do {
        if (!base[j].isUsed)
            return false;
        else if (base[j].isUsed && base[j].key == key) {
            return true;
        }
        ++j;
        j %= K;
    } while (j != i);
    return false;
}

template<typename Key, typename Value, size_t K>
Value &HashTable<Key, Value, K>::operator[](const Key &key) {
    size_t i = hash(key);
    size_t j = i;
    do {
        if (!base[j].isUsed) {
            new (base + j) Node(key, Value());
            _size++;
            return base[j].value;
        }
        else if (base[j].isUsed && base[j].key == key) {
            return base[j].value;
        }
        ++j;
        j %= K;
    } while (j != i);
    return *(new Value());
}

template<typename Key, typename Value, size_t K>
void HashTable<Key, Value, K>::erase(const Key &key) {
    size_t i = hash(key);
    size_t j = i;
    do {
        if (!base[j].isUsed) {
            return;
        } else if (base[j].isUsed && base[j].key == key) {
            base[j].isUsed = false;
            _size--;
            return;
        }
        ++j;
        j %= K;
    } while (i != j);
}

template<typename Key, typename Value, size_t K>
size_t HashTable<Key, Value, K>::hash(const Key &key) {
    double A = (sqrt(5) - 1) / 2.0;
    return static_cast<size_t>(K * fmod((key * A), 1)) % K;
}

template<typename Key, typename Value, size_t K>
void HashTable<Key, Value, K>::insert(const Key &key, const Value &value) {
    if (_size == K)
        throw std::out_of_range("not enough space in table");
    size_t i = hash(key);
    size_t j = i;
    do {
        if (!base[j].isUsed) {
            new (base + j) Node(key, value);
            _size++;
            base[j].isUsed = true;
            return;
        } else if (base[j].key == key && base[j].isUsed) {
            base[j].value = value;
            return;
        }
        ++j;
        j %= K;
    } while (i != j);
}

#endif//HASH_TABLE_H
