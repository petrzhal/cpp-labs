#pragma once
#include <iostream>
#include <forward_list>

template <typename Key>
struct hash {
	size_t operator()(const Key& key) {
		auto ptr = reinterpret_cast<const uint8_t*>(&key);
		size_t size = sizeof(Key);
		size_t hash = 0;
		for (size_t i = 0; i < size; ++i) {
			hash ^= static_cast<size_t>(*(ptr + i));
		}
		return hash;
	}
};

template <>
struct hash<std::string> {
	size_t operator()(const std::string& key) {
		size_t hash = 0;
		for (size_t i = 0; i < key.length(); i++)
		{
			hash += static_cast<size_t>(key[i]) * (i + 1);
		}
		return hash;
	}
};

template <>
struct hash<int> {
	size_t operator()(int key) {
		return static_cast<size_t>(key);
	}
};

template <typename Key, typename Value, class Hash = hash<Key>>
class unordered_map {
private:
	std::forward_list<std::pair<Key, Value>>* _base;
	size_t _size;
	size_t _capacity;
	size_t hash(const Key&);

public:
	unordered_map(size_t size = 32)
		: _base(new std::forward_list<std::pair<Key, Value>>[size] {}),
		_size(0),
		_capacity(size) {}
	void insert(const Key&, const Value&);
	void erase(const Key&);
	void rehash(size_t);
	Value& operator[](const Key&);
	bool contains(const Key&);
	void clear();
};

template <typename Key, typename Value, class Hash>
size_t unordered_map<Key, Value, Hash>::hash(const Key& key)
{
	return Hash{}(key) % _capacity;
}

template <typename Key, typename Value, class Hash>
void unordered_map<Key, Value, Hash>::insert(const Key& key, const Value& value)
{
	size_t i = hash(key);
	if (_size >= _capacity * 0.8) {
		rehash(_capacity * 2);
	}
	_base[i].emplace_front(key, value);
	++_size;
}

template<typename Key, typename Value, class Hash>
void unordered_map<Key, Value, Hash>::erase(const Key& key)
{
	size_t i = hash(key);
	if (!_size) {
		return;
	}
	auto& list = _base[i];
	auto prev = list.before_begin();
	for (auto& el : list) {
		if (el.first == key) {
			list.erase_after(prev);
			--_size;
			return;
		}
		++prev;
	}
}

template <typename Key, typename Value, class Hash>
void unordered_map<Key, Value, Hash>::rehash(size_t n)
{
	if (n > _capacity) {
		auto oldCap = _capacity;
		_capacity = n;
		auto newBase = new std::forward_list<std::pair<Key, Value>>[n] {};
		for (size_t i = 0; i < oldCap; ++i) {
			for (const auto& el : _base[i]) {
				size_t i = hash(el.first);
				newBase[i].emplace_front(el.first, el.second);
			}
		}
		delete[] _base;
		_base = newBase;
	}
}

template <typename Key, typename Value, class Hash>
Value& unordered_map<Key, Value, Hash>::operator[](const Key& key)
{
	size_t i = hash(key);
	auto& list = _base[i];
	for (auto& el : list) {
		if (el.first == key) {
			return el.second;
		}
	}
	insert(key, Value());
	return (*this)[key];
}

template <typename Key, typename Value, class Hash>
bool unordered_map<Key, Value, Hash>::contains(const Key& key)
{
	size_t i = hash(key);
	if (!_base[i])
		return false;
	for (const auto& el : _base[i]) {
		if (el.first == key) {
			return true;
		}
	}
	return false;
}

template<typename Key, typename Value, class Hash>
void unordered_map<Key, Value, Hash>::clear()
{
	delete[] _base;
	_base = nullptr;
	_size = 0;
}
