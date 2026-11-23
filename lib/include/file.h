#pragma once
#include <string>
#include <vector>

namespace mylib {

// Возвращает длину строки. Для пустой строки возвращает 0.
size_t stringLength(const std::string& s);

// Конкатенация двух строк.
std::string concatenate(const std::string& a, const std::string& b);

// Реверс строки. Для пустой строки возвращает пустую строку.
std::string reverse(const std::string& s);

// Перевод всех символов в верхний регистр.
std::string toUpperCase(const std::string& s);

// Перевод всех символов в нижний регистр.
std::string toLowerCase(const std::string& s);

// Поиск первого вхождения подстроки.
// Возвращает индекс первого вхождения или -1, если подстрока не найдена.
// Если подстрока пустая, возвращает 0.
int findSubstring(const std::string& s, const std::string& sub);

// Разбиение строки по разделителю.
// Возвращает вектор подстрок. Если строка пустая, возвращает пустой вектор.
// Несколько разделителей подряд создают пустые строки в результате.
std::vector<std::string> split(const std::string& s, char delimiter);

} // namespace mylib