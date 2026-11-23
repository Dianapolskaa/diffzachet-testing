#include "file.h"

namespace mylib {

// ===== СТЕК =====
Stack::Stack(int capacity) : capacity_(capacity), size_(0) {
    if (capacity <= 0) {
        throw std::invalid_argument("Stack capacity must be positive");
    }
    data_ = new int[capacity];
}

Stack::~Stack() {
    delete[] data_;
}

void Stack::push(int value) {
    if (isFull()) {
        throw std::runtime_error("Stack overflow");
    }
    data_[size_++] = value;
}

int Stack::pop() {
    if (isEmpty()) {
        throw std::runtime_error("Stack underflow");
    }
    return data_[--size_];
}

int Stack::peek() const {
    if (isEmpty()) {
        throw std::runtime_error("Stack is empty");
    }
    return data_[size_ - 1];
}

bool Stack::isEmpty() const { return size_ == 0; }
bool Stack::isFull() const { return size_ == capacity_; }
int Stack::size() const { return size_; }
int Stack::capacity() const { return capacity_; }

// ===== ОЧЕРЕДЬ (циклический буфер) =====
Queue::Queue(int capacity) : capacity_(capacity), front_(0), rear_(0), size_(0) {
    if (capacity <= 0) {
        throw std::invalid_argument("Queue capacity must be positive");
    }
    data_ = new int[capacity];
}

Queue::~Queue() {
    delete[] data_;
}

void Queue::enqueue(int value) {
    if (isFull()) {
        throw std::runtime_error("Queue overflow");
    }
    data_[rear_] = value;
    rear_ = (rear_ + 1) % capacity_;
    size_++;
}

int Queue::dequeue() {
    if (isEmpty()) {
        throw std::runtime_error("Queue underflow");
    }
    int value = data_[front_];
    front_ = (front_ + 1) % capacity_;
    size_--;
    return value;
}

int Queue::front() const {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    return data_[front_];
}

bool Queue::isEmpty() const { return size_ == 0; }
bool Queue::isFull() const { return size_ == capacity_; }
int Queue::size() const { return size_; }
int Queue::capacity() const { return capacity_; }

} // namespace mylib