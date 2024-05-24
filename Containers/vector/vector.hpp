#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <cstddef>
#include <iostream>
#include <cmath>
namespace mystd
{
    template <typename T>
    class vector
    {
    public:
        typedef std::size_t size_type;
        typedef T *iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;

        vector()
        {
            data = nullptr;
            _size = 0;
            _capacity = 0;
        }

        vector(const vector &c)
        {
            _capacity = c._capacity;
            data = new T[_capacity];
            _size = c._size;
            for (size_type i = 0; i < _size; i++)
            {
                data[i] = c.data[i];
            }
        }

        vector(size_type n, const T &val = T())
        {
            _capacity = n;
            _size = n;
            data = new T[_capacity];
            for (size_type i = 0; i < _size; i++)
            {
                data[i] = val;
            }
        }

        vector(iterator start, iterator end)
        {
            _size = end - start;
            _capacity = _size;
            data = new T[_capacity];
            for (size_type i = 0; i < _size; ++i)
            {
                data[i] = *start;
                start++;
            }
        }

        ~vector()
        {
            delete[] data;
        }

        vector &operator=(const vector &c)
        {
            if (this != &c)
            {
                delete[] data;
                _capacity = c._capacity;
                data = new T[_capacity];
                _size = c._size;
                for (size_type i = 0; i < _size; i++)
                {
                    data[i] = c.data[i];
                }
            }
            return *this;
        }

        bool operator==(const vector &c)
        {
            if (this->size() != c.size())
                return false;
            for (size_type i = 0; i < this->size(); i++)
            {
                if (this->data[i] != c[i])
                    return false;
            }
            return true;
        }

        T &operator[](size_type n)
        {
            return data[n];
        }

        const T &operator[](size_type n) const
        {
            return data[n];
        }

        T &at(size_type n)
        {
            if (this->size() - 1 >= n)
            {
                return data[n];
            }
            else
            {
                throw std::out_of_range("Index out of range in mystd::vector::at");
            }
        }

        T &front()
        {
            return data[0];
        }

        T &back()
        {
            return data[_size - 1];
        }

        bool empty()
        {
            if (_size == 0)
                return true;
            return false;
        }
        size_type size()
        {
            return _size;
        }

        size_type capacity()
        {
            return _capacity;
        }

        size_type max_size()
        {

            return std::numeric_limits<size_type>::max() / sizeof(T) / 2;
        }

        void reserve(size_type count)
        {
            if (count > _capacity)
            {
                T *temp = new T[count];
                _capacity = count;
                for (size_type i = 0; i < size(); i++)
                {
                    temp[i] = data[i];
                }
                delete[] data;
                data = temp;
            }
        }

        void shrink_to_fit()
        {
            if (_capacity > _size)
            {
                T *temp = new T[_size];
                _capacity = _size;
                for (size_type i = 0; i < size(); i++)
                {
                    temp[i] = data[i];
                }
                delete[] data;
                data = temp;
            }
        }

        void clear()
        {
            while (_size)
                pop_back();
        }

        void pop_back()
        {
            if (_size)
            {
                _size--;
            }
        }

        void push_back(const T &value)
        {
            if (_capacity == _size)
                reserve(2 * _size);
            data[_size] = value;
            _size++;
        }

        void resize(size_type new_size, const T &val = T())
        {
            if (new_size > _capacity)
                reserve(new_size);
            for (size_type i = _size; i < new_size; i++)
                data[i] = val;
            _size = new_size;
        }

        iterator begin()
        {
            return data;
        }

        iterator end()
        {
            return data + _size;
        }

        reverse_iterator rbegin()
        {
            return reverse_iterator(end());
        }

        reverse_iterator rend()
        {
            return reverse_iterator(begin());
        }

        iterator erase(iterator position)
        {
            if (position == end())
            {
                return end();
            }

            auto iter = position;
            ++iter;

            if (iter != end())
            {
                std::copy(iter, end(), position);
            }

            pop_back();

            return iter;
        }

        iterator erase(iterator pos1, iterator pos2)
        {
            if (pos1 == pos2)
            {
                return pos1;
            }

            auto iter = pos1;
            size_type numRemoved = std::distance(pos1, pos2);

            if (pos2 != end())
            {
                std::copy(pos2, end(), pos1);
            }

            resize(size() - numRemoved);

            return iter;
        }

        iterator insert(iterator position, const T &&value)
        {
            if (position == end())
            {
                push_back(value);
                return end() - 1;
            }
            size_type index = position - begin();
            for (size_type i = size(); i > index; --i)
            {
                data[i] = std::move(data[i - 1]);
            }

            data[index] = std::move(value);

            _size++;

            return begin() + index;
        }

        void insert(iterator position, size_type count, const T &value)
        {
            if (count == 0)
            {
                return;
            }

            size_type index = position - begin();

            if (size() + count > capacity())
            {
                reserve(size() + count);
            }

            for (size_type i = size() + count - 1; i >= index + count; --i)
            {
                data[i] = std::move(data[i - count]);
            }

            for (size_type i = 0; i < count; ++i)
            {
                data[index + i] = value;
            }

            _size += count;
        }

        void swap(vector &other)
        {
            vector<T> temp;
            temp = other;
            other = *this;
            *this = temp;
        }

    private:
        T *data;
        size_type _size;
        size_type _capacity;
    };
}
#endif
