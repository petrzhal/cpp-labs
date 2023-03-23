
template<typename first_T, typename second_T>
struct pair {
    first_T first;
    second_T second;

    pair() {
        first = first_T();
        second = second_T();
    }

    pair(const first_T& first, const second_T& second) {
        new (&this->first) first_T(first);
        new (&this->second) second_T(second);
    }

    void swap(pair<first_T, second_T>& other) {
        first_T buf1 = first;
        first = other.first;
        other.first = buf1;
        second_T buf2 = second;
        second = other.second;
        other.second = buf2;
    }

    pair<first_T, second_T>& operator=(const pair<first_T, second_T>& other) {
        first = other.first;
        second = other.second;
        return *this;
    }
};

template<typename first_T, typename second_T>
pair<first_T, second_T> make_pair(const first_T& first, const second_T& second) {
    return pair<first_T, second_T>(first, second);
}
