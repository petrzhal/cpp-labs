template<class T>
class vector
{
    T* arr;
    int _size;
    int _capacity;

    void addMemory() {
        _capacity *= 2;
        T* tmp = arr;
        arr = new T[_capacity];
        for (int i = 0; i < _size; ++i) arr[i] = tmp[i];
        delete[] tmp;
    }

public:

    vector() {
        arr = new T[1];
        _capacity = 1;
    }

    ~vector() = default;

    vector(const vector& other) {
        if (this != &other) {
            arr = other.arr;
            _size = other._size;
        }
    }

    vector(T a...) {
        int i = 0;
        arr[i] = a++;
    }

    /*vector(const vector&& other)  noexcept {
        if (this != &other) {
            arr = other.arr;
            _size = other._size;
        }
    }*/

    vector& operator=(const vector& other) {
        if (this != &other) {
            arr = other.arr;
            _size = other._size;
        }
        return *this;
    }

    /*vector& operator=(const vector&& other) noexcept {
        if (this != &other) {
            arr = other.arr;
            _size = other._size;
        }
        return *this;
    }*/

    void reserve(int n) {
        if (_size <= _capacity)
            return;
        T* newarr = reinterpret_cast<T*>(new char[n * sizeof(T)]);
        int i = 0;
        try {
            for (; i < _size; ++i) {
                new (newarr + i) T(arr[i]);
            }
        } catch (...) {
            for (int j = 0; j < i; ++j) {
                (newarr + j)->~T();
            }
            delete[] reinterpret_cast<char*>(arr);
            throw;
        }
    }

    void push_back(const T& value) {
        if (_size >= _capacity)
            addMemory();
        arr[_size++] = value;
    }

    int size() const {
        return _size;
    }

    void resize(int newSize) {
        T* newVector = new T[newSize]{};
        int minSize = newSize >= _size ? _size : newSize;

        for (int i = 0; i < minSize; ++i) {
            newVector[i] = arr[i];
        }
        delete[] arr;
        arr = newVector;
        _size = newSize;
    }

    void erase(int ind) {
        for (int i = ind; i < _size - 1; ++i) {
            T tmp = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = tmp;
        }
        _size--;
    }

    void clear() {
        if (arr) {
            delete[] arr;
        }
        arr = new T[1]{};
        _size = 0;
        _capacity = 1;
    }

    T* begin() {
        return arr;
    }

    T* end() {
        return arr + _size;
    }

    const T* begin() const {
        return arr;
    }

    const T* end() const {
        return arr + _size;
    }

    T& operator[](int index)  {
        return arr[index];
    }

    const T& operator[](int index) const {
        return arr[index];
    }
};
