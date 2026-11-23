#pragma once
#include <stdexcept>

namespace mylib {

// ===== СТЕК (LIFO) =====
class Stack {
public:
    // Конструктор с заданной ёмкостью. Бросает std::invalid_argument, если capacity <= 0.
    explicit Stack(int capacity);
     ~Stack();

    // Добавить элемент. Бросает std::runtime_error, если стек полон.
    void push(int value);

    // Удалить и вернуть верхний элемент. Бросает std::runtime_error, если стек пуст.
    int pop();

    // Вернуть верхний элемент без удаления. Бросает std::runtime_error, если стек пуст.
    int peek() const;

    bool isEmpty() const;
    bool isFull() const;
    int size() const;
    int capacity() const;

private:
    int* data_;
    int capacity_;
    int size_;
};

// ===== ОЧЕРЕДЬ (FIFO) =====
class Queue {
public:
    // Конструктор с заданной ёмкостью. Бросает std::invalid_argument, если capacity <= 0.
    explicit Queue(int capacity);
     ~Queue();

    // Добавить элемент в конец. Бросает std::runtime_error, если очередь полна.
    void enqueue(int value);

    // Удалить и вернуть первый элемент. Бросает std::runtime_error, если очередь пуста.
    int dequeue();

    // Вернуть первый элемент без удаления. Бросает std::runtime_error, если очередь пуста.
    int front() const;

    bool isEmpty() const;
    bool isFull() const;
    int size() const;
    int capacity() const;

private:
    int* data_;
    int capacity_;
    int front_;
    int rear_;
    int size_;
};

} // namespace mylib