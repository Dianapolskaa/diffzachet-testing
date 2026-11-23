#pragma once
#include <string>
#include <stdexcept>

namespace mylib {

class Complex {
public:
    // Конструктор. По умолчанию создаёт 0 + 0i.
    Complex(double real = 0.0, double imag = 0.0);

    double real() const;
    double imag() const;

    // Арифметические операции
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;

    // Деление. Бросает std::invalid_argument, если делитель равен 0+0i.
    Complex operator/(const Complex& other) const;

    // Операции сравнения (по действительной и мнимой части)
    bool operator==(const Complex& other) const;
    bool operator!=(const Complex& other) const;

    // Сопряжённое число: a + bi → a - bi
    Complex conjugate() const;

    // Модуль числа: |a + bi| = sqrt(a² + b²)
    double modulus() const;

    // Возведение в целую степень n.
    // Использует формулу Муавра для эффективности.
    // Для n < 0 вычисляет (1/z)^|n|, бросает std::invalid_argument, если z = 0 и n < 0.
    Complex power(int n) const;

    // Строковое представление: "a+bi", "a-bi", "a", "bi"
    std::string toString() const;

private:
    double real_;
    double imag_;
};

} // namespace mylib