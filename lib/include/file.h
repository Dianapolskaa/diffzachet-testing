#pragma once
#include <string>
#include <stdexcept>

namespace mylib {

class Rational {
public:
    // Конструктор. Бросает std::invalid_argument, если denominator == 0.
    // Знак дроби хранится в числителе, знаменатель всегда > 0. Дробь автоматически сокращается.
    Rational(long long numerator = 0, long long denominator = 1);

    long long numerator() const;
    long long denominator() const;

    // Арифметические операции
    Rational operator+(const Rational& other) const;
    Rational operator-(const Rational& other) const;
    Rational operator*(const Rational& other) const;
    Rational operator/(const Rational& other) const; // Бросает std::invalid_argument, если other == 0

    // Операции сравнения
    bool operator==(const Rational& other) const;
    bool operator!=(const Rational& other) const;
    bool operator<(const Rational& other) const;
    bool operator>(const Rational& other) const;
    bool operator<=(const Rational& other) const;
    bool operator>=(const Rational& other) const;

    // Возвращает строковое представление: "a/b" или просто "a", если знаменатель равен 1.
    std::string toString() const;

private:
    long long num_;
    long long den_;
    void normalize();
    static long long gcd(long long a, long long b);
};

} // namespace mylib