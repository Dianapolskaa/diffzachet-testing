#pragma once
#include <string>

namespace mylib {

// Конвертация арабского числа (1-3999) в римское.
// Если число вне диапазона, возвращает пустую строку.
std::string intToRoman(int number);

// Конвертация римского числа в арабское.
// Если строка невалидна или результат вне диапазона 1-3999, возвращает 0.
int romanToInt(const std::string& roman);

// Проверка валидности римского числа.
// Возвращает true, если строка представляет корректное римское число в диапазоне 1-3999.
bool isValidRoman(const std::string& roman);

} // namespace mylib