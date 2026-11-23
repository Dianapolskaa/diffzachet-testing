#pragma once

namespace mylib {

enum class TriangleType {
    Invalid,        // Не существует
    Equilateral,    // Равносторонний
    Isosceles,      // Равнобедренный
    Scalene         // Разносторонний
};

enum class AngleType {
    Invalid,        // Не существует
    Acute,          // Остроугольный
    Right,          // Прямоугольный
    Obtuse          // Тупоугольный
};

// Проверка существования треугольника по трём сторонам
// Возвращает true если a, b, c > 0 и выполняется неравенство треугольника
bool exists(double a, double b, double c);

// Определение типа по сторонам
// Если треугольник не существует, возвращает TriangleType::Invalid
TriangleType typeBySides(double a, double b, double c);

// Определение типа по углам
// Если треугольник не существует, возвращает AngleType::Invalid
AngleType typeByAngles(double a, double b, double c);

// Площадь по формуле Герона
// Если треугольник не существует, возвращает -1.0
double area(double a, double b, double c);

// Периметр
// Если треугольник не существует, возвращает -1.0
double perimeter(double a, double b, double c);

} // namespace mylib
