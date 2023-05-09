#pragma once
#include <iostream>
#include <vector>

template <typename T>
class heap {
private:
	std::vector<T> base;

	void siftUp(size_t i) {
		while (i) {
			if (base[(i - 1) / 2] < base[i]) {
				std::swap(base[(i - 1) / 2], base[i]);
				i = (i - 1) / 2;
			}
			else break;
		}
	}

	void siftDown(size_t i) {
		size_t left = i * 2;
		size_t right = i * 2 + 1;
		size_t largest = i;
		if (left < base.size() && base[left] > base[largest]) {
			largest = left;
		}
		if (right < base.size() && base[right] > base[largest]) {
			largest = right;
		}
		if (largest != i) {
			std::swap(base[i], base[largest]);
			siftDown(largest);
		}
	}

public:
	heap() = default;
	void insert(const T&);
	T& max();
	[[nodiscard]] size_t size() const;
	bool empty() const;
};

template<typename T>
void heap<T>::insert(const T& value)
{
	base.emplace_back(value);
	siftUp(base.size() - 1);
}

template<typename T>
T& heap<T>::max()
{
	if (base.empty()) {
		throw "empty heap";
	}
	T& res = base[0];
	base[0] = base[base.size() - 1];
	base.pop_back();
	siftDown(0);
	return res;
}

template<typename T>
size_t heap<T>::size() const
{
	return base.size();
}

template<typename T>
bool heap<T>::empty() const
{
	return base.empty();
}
