#include <algorithm>
#include <cstddef>
#include <iterator>
#include <memory>

template<typename T>
void merge_sort(T array[], std::size_t size, bool(*cmp) (const T&, const T&))
{
    if (size > 1)
    {
        std::size_t const left_size = size / 2;
        std::size_t const right_size = size - left_size;

        merge_sort(&array[0], left_size, cmp);
        merge_sort(&array[left_size], right_size, cmp);

        std::size_t lidx = 0, ridx = left_size, idx = 0;
        T* tmp_array(new T[size]);

        while (lidx < left_size || ridx < size)
        {
            if (cmp(array[lidx], array[ridx]))
            {
                tmp_array[idx++] = std::move(array[lidx]);
                lidx++;
            }
            else
            {
                tmp_array[idx++] = std::move(array[ridx]);
                ridx++;
            }

            if (lidx == left_size)
            {
                std::copy(std::make_move_iterator(&array[ridx]),
                          std::make_move_iterator(&array[size]),
                          &tmp_array[idx]);
                break;
            }
            if (ridx == size)
            {
                std::copy(std::make_move_iterator(&array[lidx]),
                          std::make_move_iterator(&array[left_size]),
                          &tmp_array[idx]);
                break;
            }
        }

        std::copy(std::make_move_iterator(tmp_array),
                  std::make_move_iterator(&tmp_array[size]),
                  array);
    }
}
