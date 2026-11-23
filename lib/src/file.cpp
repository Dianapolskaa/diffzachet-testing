#include "file.h"
#include <algorithm>

namespace mylib {

DynamicArray::DynamicArray() : data_(nullptr), size_(0), capacity_(4) {
    data_ = new int[capacity_];
}

DynamicArray::DynamicArray(int capacity) : data_(nullptr), size_(0), capacity_(capacity) {
    if (capacity <= 0) {
        throw std::invalid_argument("Capacity must be positive");
    }
    data_ = new int[capacity_];
}

DynamicArray::DynamicArray(const DynamicArray& other)
    : data_(nullptr), size_(other.size_), capacity_(other.capacity_) {
    data_ = new int[capacity_];
    for (int i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
}

DynamicArray& DynamicArray::operator=(const DynamicArray& other) {
    if (this != &other) { // Защита от самоприсваивания
        delete[] data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = new int[capacity_];
        for (int i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    return *this;
}

DynamicArray::~DynamicArray() {
    delete[] data_;
}

void DynamicArray::pushBack(int value) {
    if (size_ == capacity_) {
        resize(capacity_ * 2); // Увеличиваем ёмкость в 2 раза
    }
    data_[size_++] = value;
}

void DynamicArray::popBack() {
    if (size_ == 0) {
        throw std::runtime_error("Array is empty");
    }
    size_--;
    // Опционально: уменьшаем ёмкость, если размер упал ниже 1/4
    if (size_ > 0 && size_ <= capacity_ / 4) {
        resize(capacity_ / 2);
    }
}

void DynamicArray::insertAt(int index, int value) {
    if (index < 0 || index > size_) {
        throw std::out_of_range("Index out of bounds");
    }
    if (size_ == capacity_) {
        resize(capacity_ * 2);
    }
    // Сдвигаем элементы вправо
    for (int i = size_; i > index; --i) {
        data_[i] = data_[i - 1];
    }
    data_[index] = value;
    size_++;
}

void DynamicArray::removeAt(int index) {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Index out of bounds");
    }
    // Сдвигаем элементы влево
    for (int i = index; i < size_ - 1; ++i) {
        data_[i] = data_[i + 1];
    }
    size_--;
    if (size_ > 0 && size_ <= capacity_ / 4) {
        resize(capacity_ / 2);
    }
}

int DynamicArray::get(int index) const {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Index out of bounds");
    }
    return data_[index];
}

void DynamicArray::set(int index, int value) {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Index out of bounds");
    }
    data_[index] = value;
}

int DynamicArray::indexOf(int value) const {
    for (int i = 0; i < size_; ++i) {
        if (data_[i] == value) {
            return i;
        }
    }
    return -1;
}

int DynamicArray::size() const {
    return size_;
}

int DynamicArray::capacity() const {
    return capacity_;
}

void DynamicArray::clear() {
    size_ = 0;
}

void DynamicArray::resize(int newCapacity) {
    int* newData = new int[newCapacity];
    int copySize = std::min(size_, newCapacity);
    for (int i = 0; i < copySize; ++i) {
        newData[i] = data_[i];
    }
    delete[] data_;
    data_ = newData;
    capacity_ = newCapacity;
}

} // namespace mylib