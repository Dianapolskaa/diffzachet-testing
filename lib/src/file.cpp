#include "file.h"
#include <cmath>

namespace mylib {

long long Rational::gcd(long long a, long long b) {
    a = std::abs(a);
    b = std::abs(b);
    while (b != 0) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

void Rational::normalize() {
    if (den_ == 0) {
        throw std::invalid_argument("Denominator cannot be zero");
    }
    // Переносим знак в числитель
    if (den_ < 0) {
        num_ = -num_;
        den_ = -den_;
    }
    // Сокращаем дробь
    long long g = gcd(std::abs(num_), den_);
    if (g > 0) {
        num_ /= g;
        den_ /= g;
    }
}

Rational::Rational(long long numerator, long long denominator)
    : num_(numerator), den_(denominator) {
    normalize();
}

long long Rational::numerator() const { return num_; }
long long Rational::denominator() const { return den_; }

Rational Rational::operator+(const Rational& other) const {
    return Rational(num_ * other.den_ + other.num_ * den_, den_ * other.den_);
}

Rational Rational::operator-(const Rational& other) const {
    return Rational(num_ * other.den_ - other.num_ * den_, den_ * other.den_);
}

Rational Rational::operator*(const Rational& other) const {
    return Rational(num_ * other.num_, den_ * other.den_);
}

Rational Rational::operator/(const Rational& other) const {
    if (other.num_ == 0) {
        throw std::invalid_argument("Division by zero rational number");
    }
    return Rational(num_ * other.den_, den_ * other.num_);
}

bool Rational::operator==(const Rational& other) const {
    return num_ == other.num_ && den_ == other.den_;
}

bool Rational::operator!=(const Rational& other) const {
    return !(*this == other);
}

bool Rational::operator<(const Rational& other) const {
    return num_ * other.den_ < other.num_ * den_;
}

bool Rational::operator>(const Rational& other) const {
    return other < *this;
}

bool Rational::operator<=(const Rational& other) const {
    return !(other < *this);
}

bool Rational::operator>=(const Rational& other) const {
    return !(*this < other);
}

std::string Rational::toString() const {
    if (den_ == 1) {
        return std::to_string(num_);
    }
    return std::to_string(num_) + "/" + std::to_string(den_);
}

} // namespace mylib