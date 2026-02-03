#pragma once
#include <memory>
#include "../baseHeaders.h"

// todo reserve
//  clear
//  insert
//  erase

// todo uninit condition
//  если мы оставляем в [0, len] непроинизицализированный элемент
// todo constexpr
//  можно ли в constexpr функциях вызывать не constexpr функции?
//  как сделать Vector constexpr?

// why reserve, push_back is constexpr

namespace my {

    template<class T, class Alloc = std::allocator<T>>
    class Vector {
        T* arr = nullptr;
        size_t len = 0;
        size_t cap = 0;

        Alloc alloc;

        using AllocTraits = std::allocator_traits<Alloc>;

        [[nodiscard]]
        constexpr size_t newCapacity(size_t oldCapacity) {
            return (oldCapacity == 0) ? 1 : oldCapacity*3/2;
        }


        template<class ForwardIterator, class DestinationIterator>
        DestinationIterator uninitializedMove(ForwardIterator begin, ForwardIterator end, DestinationIterator destinationIt) {
            ForwardIterator it = begin;
            DestinationIterator current = destinationIt;
            try {
                for (; it != end; ++it) {
                    AllocTraits::construct(alloc, current, std::move_if_noexcept(*it));
                    ++current;
                }
            } catch (...) {
                for (ForwardIterator jt = begin; jt != it; ++jt) {
                    AllocTraits::construct(alloc, begin, std::move_if_noexcept(*jt));
                    ++begin;
                }
                throw;
            }
            return current;
        }

        template<class ForwardIterator, class DestinationIterator>
        DestinationIterator uninitializedCopy(ForwardIterator begin, ForwardIterator end, DestinationIterator destinationIt) {
            ForwardIterator it = begin;
            DestinationIterator current = destinationIt;
            try {
                for (; it != end; ++it) {
                    AllocTraits::construct(alloc, current, *it);
                    ++current;
                }
            } catch (...) {
                for (ForwardIterator jt = destinationIt; jt != current; ++jt) {
                    AllocTraits::destroy(alloc, jt);
                }
                throw;
            }
            return current;
        }


    public:
        Vector() = default;

        constexpr explicit Vector(size_t length, const Alloc & allocator = std::allocator<T>()) : len(length), alloc(allocator) {
            if (length > cap) {
                arr = AllocTraits::allocate(alloc, length);
                cap = length;
            } else {
                arr = AllocTraits::allocate(alloc, cap);
            }
            int i = 0;
            try {
                for (; i < length; ++i) {
                    AllocTraits::construct(alloc, arr + i, T());
                }
            } catch(...) {
                for (int j = 0; j < i; ++j) {
                    AllocTraits::destroy(alloc, arr + i);
                }
                throw;
            }
        };

        constexpr Vector(std::initializer_list<T> && list, const Alloc & allocator = std::allocator<T>()) : alloc(allocator) {
            arr = AllocTraits::allocate(alloc, list.size());
            try {
                uninitializedCopy(list.begin(), list.end(), arr);
            } catch(...) {
                AllocTraits::deallocate(alloc, arr, list.size());
            }
            cap = list.size();
            len = list.size();
        };

        constexpr ~Vector() {
            for (int i = 0; i < len; ++i) {
                AllocTraits::destroy(alloc, arr + i);
            }
            AllocTraits::deallocate(alloc, arr, cap);
        }

        ///Deletes the element at the end of the vector.
        constexpr void pop_back() {
            if (len == 0) return;
            AllocTraits::destroy(alloc, len);
            len--;
        }

        ///Adds an element to the end of the vector.
        constexpr void push_back(const T & el) {
            emplace_back(el);
        }

        constexpr void push_back(T && el) {
            emplace_back(std::move(el));
        }

        ///Adds an element constructed in place to the end of the vector.
        template<class... Types>
        constexpr T & emplace_back(Types && ... args) {
            if (len == cap) {
                reserve(newCapacity(cap));
            }
            AllocTraits::construct(alloc, arr + len, std::forward<Types>(args)...);
            ++len;
            return back();
        }

        ///Reserves a minimum length of storage for a vector object, allocating space if necessary.
        constexpr void reserve(size_t length) {
            if (length <= cap) return;
            T* newArr = AllocTraits::allocate(alloc, length);

            size_t i = 0;
            try {
                uninitializedMove(arr, arr + len, newArr);
            } catch (...) {
                uninitializedMove(newArr, newArr + i, arr);
                AllocTraits::deallocate(alloc, newArr, length);
                throw;
            }
            AllocTraits::deallocate(alloc, arr, cap);
            arr = newArr;
            cap = length;
        }

        ///Discards excess capacity.
        constexpr void shrink_to_fit() {
            if (cap == len) return;

            T *newArr = AllocTraits::allocate(alloc, len);
            size_t i = 0;
            try {
                uninitializedMove(arr, arr + len, newArr);
            } catch (...) {
                uninitializedMove(newArr, newArr + i, arr);
                AllocTraits::deallocate(alloc, newArr, len);
                throw;
            }
            AllocTraits::deallocate(alloc, arr, cap);
            arr = newArr;
            cap = len;
        }

        Vector(const Vector<T, Alloc> & other) {
            len = other.len;
            cap = other.cap;
            alloc = AllocTraits::select_on_container_copy_construction(other.alloc);
            arr = AllocTraits::allocate(alloc, other.cap);
            size_t i = 0;
            try {
                uninitializedCopy(other.arr, other.arr + other.len, arr);
            } catch (...) {
                for (int j = 0; j < i; ++j) {
                    AllocTraits::destroy(alloc, arr + i);
                }
                AllocTraits::deallocate(alloc, arr, other.cap);
                throw;
            }
        }

        ///Copy the elements of the vector with a copy of another vector.
        Vector<T, Alloc>& operator=(const Vector<T, Alloc> & other) & {
            if (&other == this) return *this;

            for (int i = 0; i < len; ++i) {
                AllocTraits::destroy(alloc, arr + i);
            }
            AllocTraits::deallocate(alloc, arr, cap);

            len = other.len;
            cap = other.cap;
            if (AllocTraits::propagate_on_container_copy_assignment::value) {
                alloc = other.alloc;
            }
            arr = AllocTraits::allocate(alloc, other.cap);
            size_t i = 0;
            try {
                uninitializedCopy(other.arr, other.arr + other.len, arr);
            } catch (...) {
                for (int j = 0; j < i; ++j) {
                    AllocTraits::destroy(alloc, arr + i);
                }
                AllocTraits::deallocate(alloc, arr, other.cap);
                throw;
            }

            return *this;
        }

        Vector(Vector<T, Alloc> && other) noexcept
                : len(other.len), cap(other.cap),
                  arr(other.arr), alloc(std::move(other.alloc)) {
            other.len = 0;
            other.cap = 0;
            other.alloc = Alloc();
            other.arr = nullptr;
        }

        ///Replaces the elements of the vector with a copy of another vector, destroys the last one.
        Vector<T, Alloc>& operator=(Vector<T, Alloc> && other) & noexcept {
            if (&other == this) return *this;

            for (int i = 0; i < len; ++i) {
                AllocTraits::destroy(alloc, arr + i);
            }
            AllocTraits::deallocate(alloc, arr, cap);

            len = other.len;
            cap = other.cap;
            alloc = std::move(alloc);
            arr = other.arr;

            other.len = 0;
            other.cap = 0;
            other.alloc = Alloc();
            other.arr = nullptr;

            return *this;
        }

        ///Returns a copy of the allocator object used to construct the vector.
        constexpr Alloc & get_allocator() const {
            return alloc;
        }

        ///Returns a capacity of the vector.
        [[nodiscard]]
        constexpr size_t capacity() const {
            return cap;
        }

        ///Returns a length of the vector.
        [[nodiscard]]
        constexpr size_t size() const {
            return len;
        }

        ///Checks if the vector is empty or not.
        [[nodiscard]]
        constexpr bool empty() const {
            return len == 0;
        }

        ///Returns the last element of the vector.
        [[nodiscard]]
        constexpr T & back() {
            return arr[len - 1];
        }

        ///Returns the last element of the vector only for reading.
        [[nodiscard]]
        constexpr const T & back() const {
            return arr[len - 1];
        }

        ///Returns the first element of the vector.
        [[nodiscard]]
        constexpr T & front() {
            return arr[0];
        }

        ///Returns the first element of the vector only for reading.
        [[nodiscard]]
        constexpr const T & front() const {
            return arr[0];
        }

        ///Returns an indexed element of the vector.
        [[nodiscard]]
        constexpr T & operator[](size_t index) {
            return arr[index];
        }

        ///Returns an indexed element of the vector only for reading.
        [[nodiscard]]
        constexpr const T & operator[](size_t index) const {
            return arr[index];
        }

        ///Returns a reference to the element at a specified location in the vector.
        [[nodiscard]]
        constexpr T & at(size_t index) {
            return (index >= len) ? throw std::out_of_range("Vector index out of range!") : arr[index];
        }

        ///Returns a reference to the element at a specified location in the vector only for reading.
        [[nodiscard]]
        constexpr const T & at(size_t index) const {
            return (index >= len) ? throw std::out_of_range("Vector index out of range!") : arr[index];
        }

        ///agregate
        ///применяем функцию func к текущему и берет прошлое значение
        ///например заполняет строку "" 12231231

        template <bool consted>
        struct Iterator {
            std::conditional_t<consted, const T, T> * ptr;

        public:
            Iterator(T * p) : ptr(p) {}

            T& operator*()
            { return *ptr; }
            T* operator->()
            { return ptr; }
            Iterator& operator++() {
                ++ptr;
                return *this;
            }

            Iterator operator++(int)
            { return *this++; }

            bool operator==(const Iterator & i) const
            { return this->ptr == i.ptr; }
            bool operator!=(const Iterator & i) const
            { return this->ptr != i.ptr; }
        };

        // итераторы
        using iterator = Iterator<false>;
        using const_iterator = Iterator<true>;

        iterator begin() const
        { return iterator(arr); }
        iterator end() const
        { return iterator(arr+len); }

        template <typename Type>
        Type aggregate(Type seed, std::function<Type (Type, const T&)> f) const {
            Type res = seed;
            for (auto el: *this)
                res = f(res, el);
            return res;
        }

        iterator insert(iterator position, std::move_iterator<iterator> first, std::move_iterator<iterator> last) {
            iterator p = position;
            for (; first != last; ++first) {
                *position = *first;
                ++position;
            }
            return p;
        }
    };


}


