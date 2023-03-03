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

        iterator<T>& operator++() {
            it++;
            return *this;
        }

        iterator<T>& operator--() {
            it--;
            return *this;
        }

        iterator<T>& operator++(int) {
            it++;
            return *this;
        }

        iterator<T>& operator--(int) {
            it--;
            return *this;
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

        iterator operator-(int n) {
            it -= n;
            return *this;
        }

        T &operator*() {
            return *it;
        }

        T* get() {
            return it;
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

        const T &operator*() {
            return *it;
        }
    };

    //create iterator from pointer
    template<class T>
    iterator<T> IterFromPointer(T* ptr) {
        return *(new iterator<T>(ptr));
    }

    //create const_iterator from pointer
    template<class T>
    const_iterator<T> cIterFromPointer(T* _ptr) {
        return *(new const_iterator<T>(_ptr));
    }
};