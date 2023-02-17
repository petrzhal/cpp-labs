template<class T>
class vector
{
    T* arr;
    int arrSize{};
    int capacity{};

    void addMemory() {
        capacity *= 2;
        T* tmp = arr;
        arr = new T[capacity];
        for (int i = 0; i < arrSize; ++i) arr[i] = tmp[i];
        delete[] tmp;
    }

public:

    vector() {
        arr = new T[1];
        capacity = 1;
    }

    ~vector() = default;

    vector(const vector& other) {
        if (this != &other) {
            arr = other.arr;
            arrSize = other.arrSize;
        }
    }

    /*vector(const vector&& other)  noexcept {
        if (this != &other) {
            arr = other.arr;
            arrSize = other.arrSize;            
        }
    }*/

    vector& operator=(const vector& other) {
        if (this != &other) {
            arr = other.arr;
            arrSize = other.arrSize;
        }
        return *this;
    }

    /*vector& operator=(const vector&& other) noexcept {
        if (this != &other) {
            arr = other.arr;
            arrSize = other.arrSize;
        }
        return *this;
    }*/

    void push_back(const T& value) {
        if (arrSize >= capacity) addMemory();
        arr[arrSize++] = value;
    }

    int size() const {
        return arrSize;
    }

    void resize(int newSize) {
        T* newVector = new T[newSize]{};
        int minSize = newSize >= arrSize ? arrSize : newSize;

        for (int i = 0; i < minSize; ++i) {
            newVector[i] = arr[i];
        }
        delete[] arr;
        arr = newVector;
        arrSize = newSize;
    }

    void erase(int ind) {
        for (int i = ind; i < arrSize - 1; ++i) {
            T tmp = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = tmp;
        }
        arrSize--;
    }

    void clear() {
        if (arr) {
            delete[] arr;
        }
        arr = new T[1]{};
        arrSize = 0;
        capacity = 1;
    }

    T* begin() {
        return arr;
    }

    T* end() {
        return arr + arrSize;
    }

    const T* begin() const {
        return arr;
    }

    const T* end() const {
        return arr + arrSize;
    }

    T& operator[](int index)  {
        return arr[index];
    }

    const T& operator[](int index) const {
        return arr[index];
    }
};
