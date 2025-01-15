#include <new>
#include <memory>
#include <exception>

#include "vector.hpp"

// public methods

template <typename T>
Vector<T>::Vector() : data(nullptr), size_(0), capacity_(0) {}

template <typename T>
Vector<T>::Vector(size_t count, const T& value)
    : data(static_cast<T*>(operator new[](count * sizeof(T)))), size_(count), capacity_(count) {
    try {
        for (size_t i = 0; i < count; i++) {
            new(data + i) T(value);
        }
    } catch (const std::bad_alloc& exception) {
        for (size_t i = 0; i < count; i++) {
            data[i].~T();
        }
        operator delete[](data);

        throw exception;
    }
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> init)
    : data(static_cast<T*>(operator new[](init.size() * sizeof(T)))), size_(0), capacity_(0) {
    try {
        std::uninitialized_copy(init.begin(), init.end(), data);
        size_ = init.size();
        capacity_ = init.size();
    } catch (...) {
        for (size_t i = 0; i < size_; ++i) {
            data[i].~T();
        }
        operator delete[](data);

        throw std::current_exception();;
    }
}

template <typename T>
Vector<T>::Vector(const Vector& other)
    : data(static_cast<T*>(operator new[](other.capacity_ * sizeof(T)))), size_(0), capacity_(0) {
    try {
        std::uninitialized_copy(other.data, other.data + other.size_, data);
        size_ = other.size_;
        capacity_ = other.capacity_;
    } catch (...) {
        operator delete[](data);

        throw std::current_exception();;
    }
}

template <typename T>
Vector<T>::Vector(Vector&& other) noexcept
    : data(other.data), size_(other.size_), capacity_(other.capacity_) {
    other.data = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

template <typename T>
Vector<T>::~Vector() {
    clear();
    operator delete[](data);
    data = nullptr;
}

template <typename T>
size_t Vector<T>::size() const noexcept { return size_; }

template <typename T>
size_t Vector<T>::capacity() const noexcept { return capacity_; }

template <typename T>
bool Vector<T>::empty() const noexcept { return size_ == 0; }

template <typename T>
void Vector<T>::reserve(size_t new_capacity) {
    if (new_capacity > capacity_) {
        reallocate(new_capacity);
    }
}

template <typename T>
void Vector<T>::resize(size_t count, const T& value) {
    if (count > size_) {
        reserve(count);
        for (size_t i = size_; i < count; i++) {
            new(data + i) T(value);
        }
    } else if (count < size_) {
        for (size_t i = count; i < size_; i++) {
            data[i].~T();
        }
    }
    size_ = count;
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this != &other) {
        Vector temp(other);
        swap(temp);
    }
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
    if (this != &other) {
        clear();
        operator delete[](data);

        data = other.data;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.data = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

template <typename T>
T& Vector<T>::operator[](size_t index) {
    return data[index];
}

template <typename T>
const T& Vector<T>::operator[](size_t index) const {
    return data[index];
}

template <typename T>
T& Vector<T>::at(size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }

    return data[index];
}

template <typename T>
const T& Vector<T>::at(size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }

    return data[index];
}

template <typename T>
T& Vector<T>::front() { return data[0]; }

template <typename T>
const T& Vector<T>::front() const { return data[0]; }

template <typename T>
T& Vector<T>::back() { return data[size_ - 1]; }

template <typename T>
const T& Vector<T>::back() const { return data[size_ - 1]; }

template <typename T>
void Vector<T>::push_back(const T& value) {
    if (size_ == capacity_) {
        reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }

    new(&data[size_]) T(value);
    size_++;
}

template <typename T>
void Vector<T>::pop_back() {
    if (size_ > 0) {
        size_--;
        data[size_].~T();
    }
}

template <typename T>
void Vector<T>::clear() noexcept {
    for (size_t i = 0; i < size_; i++) {
        data[i].~T();
    }
    size_ = 0;
}

template <typename T>
void Vector<T>::swap(Vector& other) noexcept {
    std::swap(data, other.data);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

template <typename T>
T* Vector<T>::begin() noexcept { return data; }

template <typename T>
const T* Vector<T>::begin() const noexcept { return data; }

template <typename T>
T* Vector<T>::end() noexcept { return data + size_; }

template <typename T>
const T* Vector<T>::end() const noexcept { return data + size_; }

// private methods

template <typename T>
void Vector<T>::reallocate(size_t new_capacity) {
    T* new_data = static_cast<T*>(operator new[](new_capacity * sizeof(T)));

    size_t i = 0;

    try {
        for (size_t i = 0; i < size_; i++) {
            new(new_data + i) T(std::move(data[i]));
            data[i].~T();
        }
    } catch (...) {
        for (size_t j = 0; j < i; j++) {
            new_data[j].~T();
        }
        operator delete[](new_data);

        throw std::current_exception();;
    }

    for (size_t j = 0; j < size_; j++) {
        data[j].~T();
    }

    operator delete[](data);
    data = new_data;
    capacity_ = new_capacity;
}
