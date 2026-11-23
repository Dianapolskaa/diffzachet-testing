#include "file.h"
#include <algorithm>

namespace mylib {

bool ascending(int a, int b) {
    return a < b;
}

bool descending(int a, int b) {
    return a > b;
}

void bubbleSort(std::vector<int>& arr, const Comparator& comp) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; ++j) {
            if (comp(arr[j + 1], arr[j])) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break; // Оптимизация: если массив уже отсортирован
    }
}

void insertionSort(std::vector<int>& arr, const Comparator& comp) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && comp(key, arr[j])) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void mergeSort(std::vector<int>& arr, const Comparator& comp) {
    if (arr.size() <= 1) return;

    int mid = arr.size() / 2;
    std::vector<int> left(arr.begin(), arr.begin() + mid);
    std::vector<int> right(arr.begin() + mid, arr.end());

    mergeSort(left, comp);
    mergeSort(right, comp);

    // Слияние
    int i = 0, j = 0, k = 0;
    while (i < left.size() && j < right.size()) {
        if (comp(left[i], right[j])) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }
    while (i < left.size()) arr[k++] = left[i++];
    while (j < right.size()) arr[k++] = right[j++];
}

} // namespace mylib