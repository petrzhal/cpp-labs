namespace it {
    template<class T>
    class iterator {
    protected:
        T *it;
    public:
        iterator() {
            it = nullptr;
        }

        explicit iterator(T *iter) {
            it = iter;
        }

        void operator++() {
            it++;
        }

        void operator--() {
            it--;
        }

        T *operator->() {
            return it;
        }

        virtual bool operator!=(const iterator &other) {
            return it != other.it;
        }

        iterator& operator=(const iterator &other) {
            it = other.it;
            return *this;
        }

        iterator& operator=(const iterator *other) {
            it = other->it;
            return *this;
        }

        iterator operator+(int n) {
            it += n;
            return *this;
        }

        T &operator*() {
            return *it;
        }
    };

    template<class T>
    class const_iterator : public iterator<T> {
    private:
        const T* it;
    public:
        const_iterator() {
            it = nullptr;
        }

        explicit const_iterator(T *iter) {
            it = iter;
        }

        const T *operator->() {
            return it;
        }

        bool operator!=(const const_iterator &other) {
            return it != other.it;
        }

        const_iterator& operator=(const const_iterator &other) {
            it = other.it;
            return *this;
        }

        const_iterator operator+(int n) {
            it += n;
            return *this;
        }

        const T &operator*() {
            return *it;
        }
    };

    //returns iterator from pointer _ptr
    template<class T>
    iterator<T> IterFromPointer(T* ptr) {
        return *(new iterator<T>(ptr));
    }

    //returns const_iterator from const pointer _ptr
    template<class T>
    const_iterator<T> cIterFromPointer(const T* _ptr) {
        return *(new const_iterator<T>(_ptr));
    }
};