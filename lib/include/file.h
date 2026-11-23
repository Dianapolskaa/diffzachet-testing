#pragma once
#include <stdexcept>

namespace mylib {

class LinkedList {
public:
    LinkedList();
    ~LinkedList();

    // Запрещаем копирование, чтобы не было двойного освобождения памяти
    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    // Вставка в начало списка.
    void insertAtHead(int value);

    // Вставка в конец списка.
    void insertAtTail(int value);

    // Вставка по индексу. Индексы начинаются с 0.
    // Бросает std::out_of_range, если index < 0 или index > size().
    void insertAtIndex(int index, int value);

    // Удаление первого вхождения значения.
    // Возвращает true, если элемент был найден и удалён, false если не найден.
    bool removeByValue(int value);

    // Получение элемента по индексу.
    // Бросает std::out_of_range, если index < 0 или index >= size().
    int get(int index) const;

    // Поиск индекса первого вхождения значения.
    // Возвращает индекс или -1, если значение не найдено.
    int indexOf(int value) const;

    // Возвращает текущее количество элементов.
    int size() const;

    // Полная очистка списка.
    void clear();

private:
    struct Node {
        int data;
        Node* next;
    };

    Node* head_;
    int size_;
};

} // namespace mylib