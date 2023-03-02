namespace it {
    template<class T>
    class iterator {
    private:
        T *it;
    public:
        iterator() {
            it = nullptr;
        }

        iterator(T *iter) {
            it = iter;
        }

        virtual void operator++() {
            it++;
        }

        virtual void operator--() {
            it--;
        }

        virtual T *operator->() {
            return it;
        }

        virtual bool operator!=(const iterator &other) {
            return it != other.it;
        }

        virtual iterator& operator=(const iterator &other) {
            it = other.it;
            return *this;
        }

        virtual iterator operator+(int n) {
            it += n;
            return *this;
        }

        virtual T &operator*() {
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

        const_iterator(T *iter) {
            it = iter;
        }

        const T *operator->() override {
            return it;
        }

        bool operator!=(const const_iterator &other) override {
            return it != other.it;
        }

        const_iterator& operator=(const const_iterator &other) override {
            it = other.it;
            return *this;
        }

        const_iterator operator+(int n) override {
            it += n;
            return *this;
        }

        const T &operator*() override {
            return *it;
        }
    };
};