#pragma once
#include <iostream>
#include "weak_ptr.h"

template <typename T>
class heap {
private:
	struct Node {
		shared_ptr<Node> next;
		weak_ptr<Node> prev;
		T data;
		Node(const T& value)
			: data(value),
			next(nullptr),
			prev(next) {}
		Node()
			: data(T()),
			next(nullptr),
			prev(next) {}
	};

	shared_ptr<Node> _begin;
	shared_ptr<Node> _end;
	size_t _size;

	void siftUp(shared_ptr<Node>);
	void siftDown(shared_ptr<Node>);

public:
	heap()
		: _begin(nullptr),
		_end(nullptr),
		_size(0) {}
	void insert(const T&);
	T& min();
	[[nodiscard]] size_t size() const;
};

template<typename T>
size_t heap<T>::size() const {
	return _size;
}

template<typename T>
void heap<T>::siftUp(shared_ptr<Node> node)
{
	if (!(node->prev.lock()))
		return;
	if (node->data < node->prev.lock()->data) {
		auto prev = node->prev.lock();
		auto tmp = node->data;
		node->data = prev->data;
		prev->data = tmp;
		siftUp(node->prev.lock());
	}
}

template<typename T>
void heap<T>::siftDown(shared_ptr<Node> node)
{
	if (!node->next)
		return;
	auto child = node->next;
	if (child->next.get() && child->next->data < child->data) {
		child = child->next;
	}
	if (child->data < node->data) {
		auto tmp = node->data;
		node->data = child->data;
		child->data = tmp;
		siftDown(child);
	}
}

template <typename T>
void heap<T>::insert(const T& value) {
	auto newNode = make_shared<Node>(value);
	if (!_size) {
		_begin = _end = newNode;
	}
	else {
		_end->next = newNode;
		newNode->prev = _end;
		_end = newNode;
		siftUp(newNode);
	}
	_size++;
}

template<typename T>
T& heap<T>::min()
{
	if (!_size) {
		throw std::out_of_range("empty heap");
	}
	auto res = _begin->data;
	if (_begin == _end) {
		_begin.reset();
		_end = nullptr;
		_begin = nullptr;
	}
	else {
		_begin->data = _end->data;
		//auto tmp = _end;
		_end = _end->prev.lock();
		_end->next = nullptr;
		//tmp.reset();
		siftDown(_begin);
	}
	--_size;
	return res;
}

