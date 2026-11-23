#pragma once
#include <vector>
#include <functional>
#include <stdexcept>

namespace mylib {

// Тип компаратора: возвращает true, если a должно идти перед b.
using Comparator = std::function<bool(int, int)>;

// Пузырьковая сортировка. Стабильная, O(n²).
void bubbleSort(std::vector<int>& arr, const Comparator& comp);

// Сортировка вставками. Стабильная, O(n²).
void insertionSort(std::vector<int>& arr, const Comparator& comp);

// Сортировка слиянием. Стабильная, O(n log n).
void mergeSort(std::vector<int>& arr, const Comparator& comp);

// Компаратор по возрастанию (по умолчанию).
bool ascending(int a, int b);

// Компаратор по убыванию.
bool descending(int a, int b);

} // namespace mylib