#include "file.h"
#include <algorithm>
#include <cctype>

namespace mylib {

size_t stringLength(const std::string& s) {
    return s.length();
}

std::string concatenate(const std::string& a, const std::string& b) {
    return a + b;
}

std::string reverse(const std::string& s) {
    std::string result = s;
    std::reverse(result.begin(), result.end());
    return result;
}

std::string toUpperCase(const std::string& s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::toupper(c); });
    return result;
}

std::string toLowerCase(const std::string& s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return result;
}

int findSubstring(const std::string& s, const std::string& sub) {
    if (sub.empty()) {
        return 0; // Пустая подстрока найдена в начале
    }
    size_t pos = s.find(sub);
    if (pos == std::string::npos) {
        return -1;
    }
    return static_cast<int>(pos);
}

std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> result;
    if (s.empty()) {
        return result; // Пустая строка → пустой вектор
    }

    std::string current;
    for (char c : s) {
        if (c == delimiter) {
            result.push_back(current);
            current.clear();
        } else {
            current += c;
        }
    }
    result.push_back(current); // Добавляем последнюю часть

    return result;
}

} // namespace mylib