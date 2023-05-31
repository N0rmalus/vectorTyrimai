#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
#include <chrono>

using std::allocator;
using std::allocator_traits;
using std::uninitialized_copy;
using std::vector;
using std::copy;
using std::cout;
using std::count;
using std::endl;
using std::cin;
using std::max;


template <class T>
class Vector {
    public:
        typedef T* iterator; 
        typedef const T* const_iterator; 
        typedef size_t size_type;
        typedef T value_type;

        Vector() { create(); }
        explicit Vector(size_type n, const T& val = T{}) { create(n, val); }
        Vector(const Vector& v) {create(v.begin(), v.end()); }
        ~Vector() { uncreate(); }

        Vector& operator=(const Vector& rhs) {
            if(&rhs != this) {
                uncreate();
                create(rhs.begin(), rhs.end());
            }
            return *this;
        } 
        Vector& operator=(const std::vector<T>& other) {
            if (this != &other) {
                uncreate();
                create(other.begin(), other.end());
            }
            return *this;
        }

        size_type size() const { return avail - data; }
        // size_type capacity() const { return limit - data; }
        T& operator[](size_type i) { return data[i]; }
        const T& operator[](size_type i) const { return data[i]; }

        iterator begin() { return data; }
        const_iterator begin() const { return data; }
        iterator end() { return limit; }
        const_iterator end() const { return limit; }

        void push_back(const T& val) {
            if(avail == limit)
                grow();
            unchecked_append(val);
        } void resize(size_type new_size, const T& val = T{}) {
            if(new_size < size()) {
                iterator new_limit = data + new_size;
                while(limit != new_limit)
                    alloc.destroy(--limit);
            }
            else if(new_size > size()) {
                if(new_size > capacity())
                    reserve(new_size);
                iterator new_limit = data + new_size;
                while (limit != new_limit)
                    unchecked_append(val);
            }
            limit = data + new_size;
        } void reserve(size_type new_capacity) {
            if(new_capacity > capacity()) {
                iterator new_data = alloc.allocate(new_capacity);
                iterator new_avail = uninitialized_copy(data, avail, new_data);
                uncreate();
                data = new_data;
                avail = new_avail;
                limit = data + new_capacity;
            }
        } void pop_back() {
            if(avail != data)
                alloc.destroy(--avail);
        }
        void clear() { uncreate();}
        bool empty() const { return data == avail; }
        size_type capacity() const { return limit - data; }
        
        iterator erase(iterator pos) {
            if(pos < begin() || pos >= end())
                throw std::out_of_range("Invalid iterator position");

            iterator new_end = pos;
            alloc.destroy(new_end++);
            while(new_end != end()) {
                *pos++ = *new_end++;
            }
            --avail;

            return pos;
        }
        iterator nth_element(iterator first, iterator nth, iterator last) {
            if (nth < first || nth >= last)
                throw std::out_of_range("Invalid iterator position");

            while (true) {
                iterator pivot = partition(first, last);
                if (pivot == nth)
                    return pivot;
                else if (pivot < nth)
                    first = pivot + 1;
                else
                    last = pivot;
            }
        }
    private:
        iterator data;
        iterator avail;
        iterator limit;

        allocator<T> alloc;

        iterator partition(iterator first, iterator last) {
            T& pivot = *first;
            iterator i = first + 1;
            iterator j = last - 1;

            while (true) {
                while (i < last && *i <= pivot)
                    ++i;
                while (j > first && *j >= pivot)
                    --j;

                if (i >= j)
                    break;

                std::swap(*i, *j);
            }

            std::swap(*first, *j);
            return j;
        }
        void create() {
            data = avail = limit = nullptr;
        }
        void create(size_type n, const T& val) {
            data = alloc.allocate(n);
            limit = avail = data + n;
            uninitialized_fill(data, limit, val);
        }
        void create(const_iterator i, const_iterator j) {
            data = alloc.allocate(j - i);
            limit = avail = uninitialized_copy(i,j,data);
        }
        void uncreate() {
            if (data) {
                iterator it = avail;
                while (it != data)
                    alloc.destroy(--it);
                alloc.deallocate(data, limit - data);
            }
            data = limit = avail = nullptr;
        }
        void grow() {
            size_type new_size = max(2 * (limit - data), ptrdiff_t(1));

            iterator new_data = alloc.allocate(new_size);
            iterator new_avail = uninitialized_copy(data, avail, new_data);

            uncreate();

            data = new_data;
            avail = new_avail;
            limit = data + new_size;
        }
        void unchecked_append(const T& val) {
            allocator_traits<allocator<T>>::construct(alloc, avail++, val);
        }
};
