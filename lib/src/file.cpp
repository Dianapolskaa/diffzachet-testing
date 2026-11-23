#include "file.h"
#include <cctype>
#include <algorithm>

namespace mylib {

bool isValidEmail(const std::string& email) {
    if (email.empty()) return false;

    // Считаем количество '@'
    int atCount = 0;
    size_t atPos = std::string::npos;
    for (size_t i = 0; i < email.size(); ++i) {
        if (email[i] == '@') {
            atCount++;
            atPos = i;
        }
    }
    if (atCount != 1) return false;

    // Локальная и доменная части
    std::string local = email.substr(0, atPos);
    std::string domain = email.substr(atPos + 1);

    if (local.empty() || domain.empty()) return false;

    // Проверка локальной части
    for (char c : local) {
        if (!std::isalnum(static_cast<unsigned char>(c)) &&
            c != '.' && c != '_' && c != '-' && c != '+') {
            return false;
        }
    }

    // Домен не должен начинаться/заканчиваться точкой или дефисом
    if (domain.front() == '.' || domain.front() == '-' ||
        domain.back() == '.' || domain.back() == '-') {
        return false;
    }

    // Домен должен содержать хотя бы одну точку
    if (domain.find('.') == std::string::npos) return false;

    // После последней точки должна быть хотя бы одна буква
    size_t lastDot = domain.rfind('.');
    if (lastDot + 1 >= domain.size()) return false;
    std::string tld = domain.substr(lastDot + 1);
    bool hasLetter = false;
    for (char c : tld) {
        if (std::isalpha(static_cast<unsigned char>(c))) {
            hasLetter = true;
            break;
        }
    }
    if (!hasLetter) return false;

    // Проверка символов домена (буквы, цифры, '.', '-')
    for (char c : domain) {
        if (!std::isalnum(static_cast<unsigned char>(c)) && c != '.' && c != '-') {
            return false;
        }
    }

    return true;
}

bool isValidPhone(const std::string& phone) {
    if (phone.empty()) return false;

    // Собираем только цифры
    std::string digits;
    for (char c : phone) {
        if (std::isdigit(static_cast<unsigned char>(c))) {
            digits += c;
        } else if (c != '+' && c != '(' && c != ')' && c != '-' && c != ' ') {
            return false; // Недопустимый символ
        }
    }

    if (digits.size() != 10 && digits.size() != 11) return false;

    if (digits.size() == 11) {
        if (digits[0] != '7' && digits[0] != '8') return false;
    }

    return true;
}

bool isValidPassword(const std::string& password) {
    if (password.size() < 8) return false;

    bool hasLetter = false;
    bool hasDigit = false;
    bool hasSpecial = false;

    const std::string specialChars = "!@#$%^&*()_+-=[]{}|;:'\",.<>?/~`";

    for (char c : password) {
        if (std::isalpha(static_cast<unsigned char>(c))) hasLetter = true;
        else if (std::isdigit(static_cast<unsigned char>(c))) hasDigit = true;
        else if (specialChars.find(c) != std::string::npos) hasSpecial = true;
    }

    return hasLetter && hasDigit && hasSpecial;
}

bool isValidAge(int age) {
    return age >= 0 && age <= 150;
}

} // namespace mylib