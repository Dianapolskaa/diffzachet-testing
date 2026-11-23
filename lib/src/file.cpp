#include "file.h"
#include <cmath>
#include <sstream>
#include <iomanip>

namespace mylib {

Complex::Complex(double real, double imag) : real_(real), imag_(imag) {}

double Complex::real() const { return real_; }
double Complex::imag() const { return imag_; }

Complex Complex::operator+(const Complex& other) const {
    return Complex(real_ + other.real_, imag_ + other.imag_);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(real_ - other.real_, imag_ - other.imag_);
}

Complex Complex::operator*(const Complex& other) const {
    // (a+bi)(c+di) = (ac-bd) + (ad+bc)i
    return Complex(
        real_ * other.real_ - imag_ * other.imag_,
        real_ * other.imag_ + imag_ * other.real_
        );
}

Complex Complex::operator/(const Complex& other) const {
    double denom = other.real_ * other.real_ + other.imag_ * other.imag_;
    if (denom == 0.0) {
        throw std::invalid_argument("Division by zero complex number");
    }
    // (a+bi)/(c+di) = (ac+bd)/(c²+d²) + (bc-ad)/(c²+d²)i
    return Complex(
        (real_ * other.real_ + imag_ * other.imag_) / denom,
        (imag_ * other.real_ - real_ * other.imag_) / denom
        );
}

bool Complex::operator==(const Complex& other) const {
    return real_ == other.real_ && imag_ == other.imag_;
}

bool Complex::operator!=(const Complex& other) const {
    return !(*this == other);
}

Complex Complex::conjugate() const {
    return Complex(real_, -imag_);
}

double Complex::modulus() const {
    return std::sqrt(real_ * real_ + imag_ * imag_);
}

Complex Complex::power(int n) const {
    if (n == 0) {
        return Complex(1.0, 0.0); // z^0 = 1
    }

    if (n < 0) {
        // z^(-n) = (1/z)^n
        if (real_ == 0.0 && imag_ == 0.0) {
            throw std::invalid_argument("Cannot raise zero to negative power");
        }
        Complex inv = Complex(1.0, 0.0) / *this;
        return inv.power(-n);
    }

    // Формула Муавра: z^n = r^n * (cos(n*θ) + i*sin(n*θ))
    double r = modulus();
    double theta = std::atan2(imag_, real_);

    double rPow = std::pow(r, n);
    return Complex(
        rPow * std::cos(n * theta),
        rPow * std::sin(n * theta)
        );
}

std::string Complex::toString() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);

    if (imag_ == 0.0) {
        oss << real_;
    } else if (real_ == 0.0) {
        oss << imag_ << "i";
    } else {
        oss << real_ << (imag_ > 0 ? "+" : "") << imag_ << "i";
    }

    return oss.str();
}

} // namespace mylib