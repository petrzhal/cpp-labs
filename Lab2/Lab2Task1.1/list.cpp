#include <iostream>
#include "abiturient.h"

struct element {
    abiturient data;
    element* next;
    element* prev;
};

class list {
private:
    element* _begin;
    element* _end;
    int count;

    element* Move(int ind) {
        element* it = _begin;
        for (int i = 0; i < ind; ++i) {
            it = it->next;
        }
        return it;
    }

    bool IsCorrectIndex(int i) {
        return (i <= count) && (i >= 0);
    }

public:
    list() {
        _begin = nullptr;
        _end = nullptr;
        count = 0;
    }

    list(const list& lst) {
        _begin = lst._begin;
        _end = lst._end;
        count = lst.count;
    }

    void addEnd(const abiturient& data) {
        auto elem = new element();
        elem->data = data;
        if (!count) {
            elem->prev = nullptr;
            elem->next = nullptr;
            _begin = _end = elem;
        }
        else {
            elem->prev = _end;
            elem->next = nullptr;
            _end->next = elem;
            _end = elem;
        }
        count++;
    }

    void addBegin(const abiturient& data) {
        auto elem = new element();
        elem->data = data;
        if (!count) {
            elem->prev = nullptr;
            elem->next = nullptr;
            _begin = _end = elem;
        }
        else {
            elem->prev = nullptr;
            elem->next = _begin;
            _begin->prev = elem;
            _begin = elem;
        }
        count++;
    }

    void insert(const abiturient& data, int ind) {
        if (!IsCorrectIndex(ind))
            return;

        if (ind == count) {
            addEnd(data);
            return;
        }
        else if (ind == 0) {
            addBegin(data);
            return;
        }
        else {
            auto elem = new element();
            elem->data = data;
            element *elemPrev = Move(ind - 1);
            element *elemNext = Move(ind);
            elem->prev = elemPrev;
            elem->next = elemNext;
            elemPrev->next = elem;
            elemNext->prev = elem;
            count++;
        }
    }

    void erase(int i) {
        if (!count || (i < 0 && i >= count))
            return;
        if (!i) {
            element *elem = Move(i);
            element *next = elem->next;
            _begin = next;
            next->prev = nullptr;
            delete elem;
            count--;
        }
        else if (i == count - 1) {
            element *elem = Move(i);
            element *prev = elem->prev;
            _end = prev;
            prev->next = nullptr;
            delete elem;
            count--;
        }
        else {
            element *elem = Move(i);
            element *next = elem->next;
            element *prev = elem->prev;
            next->prev = prev;
            prev->next = next;
            delete elem;
            count--;
        }
    }

    void clear() {
        element* cur = _begin;
        for (int i = 0; i < count - 1; ++i) {
            cur = cur->next;
            delete cur->prev;
        }
        count = 0;
        _begin = nullptr;
        _end = nullptr;
    }

    abiturient& getElement(int ind) {
        element* elem = _begin;
        for (int i = 0; i < ind; ++i) {
            elem = elem->next;
        }
        return elem->data;
    }

    /*void print(const std::string& message) {
        std::cout << message;
        for (int i = 0; i < count; ++i) {
            std::cout << getElement(i) << " ";
        }
    }

    void print() {
        for (int i = 0; i < count; ++i) {
            std::cout << getElement(i) << " ";
        }
    }*/

     [[nodiscard]] int size() const {
        return count;
    }

    element* begin() {
        return this->_begin;
    }

    element* end() {
        return this->_end;
    }

    list& operator=(const list &other) {
        _begin = other._begin;
        _end = other._end;
        count = other.count;
        return *this;
    }

    abiturient& operator[](int ind) {
        return getElement(ind);
    }
};
