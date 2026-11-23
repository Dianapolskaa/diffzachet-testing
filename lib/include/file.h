#pragma once

namespace mylib {

enum class TriangleType {
    Invalid,        // Не существует (в т.ч. нулевые/отрицательные стороны или нарушение неравенства)
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

// Проверка существования треугольника по трём сторонам (неравенство треугольника).
// Порядок сторон не влияет на результат.
// Возвращает true, если a, b, c > 0 и a+b>c, a+c>b, b+c>a.
bool exists(double a, double b, double c);

// Определение вида по сторонам.
// Если треугольник не существует, возвращает TriangleType::Invalid.
// Порядок сторон не влияет на результат.
TriangleType typeBySides(double a, double b, double c);

// Определение вида по углам.
// Если треугольник не существует, возвращает AngleType::Invalid.
// Порядок сторон не влияет на результат.
AngleType typeByAngles(double a, double b, double c);

// Площадь по формуле Герона.
// Если треугольник не существует, возвращает -1.0.
double area(double a, double b, double c);

} // namespace mylib