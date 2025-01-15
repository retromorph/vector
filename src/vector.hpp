#ifndef VECTOR_H
#define VECTOR_H

#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <cstddef>

template <typename T>
class Vector {
private:
    T* data_;
    size_t size_;
    size_t capacity_;

    void reallocate(size_t new_capacity);

public:
    Vector();
    explicit Vector(size_t count, const T& value = T());
    Vector(std::initializer_list<T> init);
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    ~Vector();

    size_t size() const noexcept;
    size_t capacity() const noexcept;
    bool empty() const noexcept;
    void reserve(size_t new_capacity);
    void resize(size_t count, const T& value = T());

    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;

    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    T& at(size_t index);
    const T& at(size_t index) const;
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

    void push_back(const T& value);
    void pop_back();
    void clear() noexcept;
    void swap(Vector& other) noexcept;

    T* begin() noexcept;
    const T* begin() const noexcept;
    T* end() noexcept;
    const T* end() const noexcept;
};

#include "vector.cpp"

#endif
