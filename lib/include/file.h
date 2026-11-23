#pragma once
#include <stdexcept>

namespace mylib {

class DynamicArray {
public:
    // Конструктор по умолчанию. Начальная ёмкость = 4.
    DynamicArray();

    // Конструктор с заданной начальной ёмкостью.
    // Бросает std::invalid_argument, если capacity <= 0.
    explicit DynamicArray(int capacity);

    // Конструктор копирования (правило трёх).
    DynamicArray(const DynamicArray& other);

    // Оператор присваивания (правило трёх).
    DynamicArray& operator=(const DynamicArray& other);

    // Деструктор (правило трёх).
    ~DynamicArray();

    // Добавить элемент в конец. При переполнении ёмкость увеличивается в 2 раза.
    void pushBack(int value);

    // Удалить последний элемент.
    // Бросает std::runtime_error, если массив пуст.
    void popBack();

    // Вставить элемент по индексу. Элементы справа сдвигаются.
    // Бросает std::out_of_range, если index < 0 или index > size().
    void insertAt(int index, int value);

    // Удалить элемент по индексу. Элементы справа сдвигаются влево.
    // Бросает std::out_of_range, если index < 0 или index >= size().
    void removeAt(int index);

    // Получить элемент по индексу.
    // Бросает std::out_of_range, если index < 0 или index >= size().
    int get(int index) const;

    // Установить элемент по индексу.
    // Бросает std::out_of_range, если index < 0 или index >= size().
    void set(int index, int value);

    // Найти индекс первого вхождения значения. Возвращает -1, если не найдено.
    int indexOf(int value) const;

    // Текущее количество элементов.
    int size() const;

    // Текущая ёмкость (сколько элементов можно добавить без перераспределения).
    int capacity() const;

    // Полная очистка массива (size = 0, capacity не меняется).
    void clear();

private:
    int* data_;
    int size_;
    int capacity_;

    // Вспомогательный метод для перераспределения памяти.
    void resize(int newCapacity);
};

} // namespace mylib