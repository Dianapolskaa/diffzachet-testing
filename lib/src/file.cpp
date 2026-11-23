#include "file.h"
#include <vector>
#include <algorithm>

namespace mylib {

// Таблица соответствий: арабское → римское (в порядке убывания)
static const std::vector<std::pair<int, std::string>> romanTable = {
    {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
    {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
    {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
};

std::string intToRoman(int number) {
    if (number < 1 || number > 3999) {
        return ""; // Вне диапазона
    }

    std::string result;
    for (const auto& [value, symbol] : romanTable) {
        while (number >= value) {
            result += symbol;
            number -= value;
        }
    }
    return result;
}

int romanToInt(const std::string& roman) {
    if (!isValidRoman(roman)) {
        return 0; // Невалидная строка
    }

    int result = 0;
    int prev = 0;

    // Идём справа налево
    for (int i = (int)roman.size() - 1; i >= 0; --i) {
        int curr = 0;
        switch (roman[i]) {
        case 'I': curr = 1; break;
        case 'V': curr = 5; break;
        case 'X': curr = 10; break;
        case 'L': curr = 50; break;
        case 'C': curr = 100; break;
        case 'D': curr = 500; break;
        case 'M': curr = 1000; break;
        }

        if (curr < prev) {
            result -= curr; // Вычитающая комбинация (IV, IX, и т.д.)
        } else {
            result += curr;
        }
        prev = curr;
    }

    return result;
}

bool isValidRoman(const std::string& roman) {
    if (roman.empty()) {
        return false;
    }

    // 1. Проверка допустимых символов
    for (char c : roman) {
        if (c != 'I' && c != 'V' && c != 'X' && c != 'L' &&
            c != 'C' && c != 'D' && c != 'M') {
            return false;
        }
    }

    // 2. Проверка недопустимых повторений (VV, LL, DD, IIII, XXXX, CCCC, MMMM)
    if (roman.find("IIII") != std::string::npos ||
        roman.find("XXXX") != std::string::npos ||
        roman.find("CCCC") != std::string::npos ||
        roman.find("MMMM") != std::string::npos ||
        roman.find("VV") != std::string::npos ||
        roman.find("LL") != std::string::npos ||
        roman.find("DD") != std::string::npos) {
        return false;
    }

    // 3. Проверка недопустимых вычитающих комбинаций
    for (size_t i = 0; i + 1 < roman.size(); ++i) {
        char curr = roman[i];
        char next = roman[i + 1];

        // Допустимые пары: IV, IX, XL, XC, CD, CM
        bool valid = false;
        if (curr == 'I' && (next == 'V' || next == 'X')) valid = true;
        if (curr == 'X' && (next == 'L' || next == 'C')) valid = true;
        if (curr == 'C' && (next == 'D' || next == 'M')) valid = true;

        int currVal = 0, nextVal = 0;
        switch (curr) {
        case 'I': currVal = 1; break;
        case 'V': currVal = 5; break;
        case 'X': currVal = 10; break;
        case 'L': currVal = 50; break;
        case 'C': currVal = 100; break;
        case 'D': currVal = 500; break;
        case 'M': currVal = 1000; break;
        }
        switch (next) {
        case 'I': nextVal = 1; break;
        case 'V': nextVal = 5; break;
        case 'X': nextVal = 10; break;
        case 'L': nextVal = 50; break;
        case 'C': nextVal = 100; break;
        case 'D': nextVal = 500; break;
        case 'M': nextVal = 1000; break;
        }

        if (currVal < nextVal && !valid) {
            return false; // Невалидная вычитающая комбинация (например, IC, IL)
        }
    }

    // 4. Вычисляем значение для проверки диапазона 1-3999
    // (Без вызова romanToInt, чтобы избежать бесконечной рекурсии!)
    int result = 0;
    int prev = 0;
    for (int i = (int)roman.size() - 1; i >= 0; --i) {
        int curr = 0;
        switch (roman[i]) {
        case 'I': curr = 1; break;
        case 'V': curr = 5; break;
        case 'X': curr = 10; break;
        case 'L': curr = 50; break;
        case 'C': curr = 100; break;
        case 'D': curr = 500; break;
        case 'M': curr = 1000; break;
        }
        if (curr < prev) {
            result -= curr;
        } else {
            result += curr;
        }
        prev = curr;
    }

    return result >= 1 && result <= 3999;
}

} // namespace mylib