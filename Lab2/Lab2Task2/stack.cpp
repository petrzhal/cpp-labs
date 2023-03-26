
template<class T>
class stack {
private:
    struct Node {
        Node* _next;
        T _data;
    };

    int _size;
    Node* _top;
public:
    stack() {
        _size = 0;
        Node* top = new Node();
        top->_next = nullptr;
    }
    ~stack() {
        Node* tmp = _top;
        for (int i = 0; i < _size; ++i) {
            Node* buf = tmp->_next;
            delete tmp;
            tmp = buf;
        }
    }
    void push(const T& newElement) {
        Node* newEl = new Node();
        newEl->_data = newElement;
        if (_size > 0) {
            newEl->_next = _top;
            _top = newEl;
        }
        else {
            newEl->_next = nullptr;
            _top = newEl;
        }
        _size++;
    }
    T& top() {
        return _top->_data;
    }
    void pop() {
        if (_size > 0) {
            Node* tmp = _top->_next;
            if (_top)
            delete _top;
            _top = tmp;
            _size--;
        }
    }
    int size() {
        return _size;
    }
};
