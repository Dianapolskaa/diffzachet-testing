#pragma once
#include <stdexcept>

namespace mylib {

// ===== ВЕКТОР 2D =====
struct Vector2 {
    double x = 0.0;
    double y = 0.0;
};

// Сумма и разность векторов.
Vector2 add(const Vector2& a, const Vector2& b);
Vector2 sub(const Vector2& a, const Vector2& b);

// Скалярное произведение.
double dot(const Vector2& a, const Vector2& b);

// Векторное произведение в 2D (z-компонента псевдовектора).
// Положительно, если b лежит против часовой стрелки от a.
double cross(const Vector2& a, const Vector2& b);

// Длина вектора.
double length(const Vector2& v);

// Нормализация. Бросает std::invalid_argument, если вектор нулевой.
Vector2 normalize(const Vector2& v);

// Угол между векторами в радианах [0, pi].
// Бросает std::invalid_argument, если хотя бы один вектор нулевой.
double angle(const Vector2& a, const Vector2& b);

// ===== ВЕКТОР 3D =====
struct Vector3 {
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
};

Vector3 add(const Vector3& a, const Vector3& b);
Vector3 sub(const Vector3& a, const Vector3& b);

double dot(const Vector3& a, const Vector3& b);

// Векторное произведение в 3D.
Vector3 cross(const Vector3& a, const Vector3& b);

double length(const Vector3& v);

// Нормализация. Бросает std::invalid_argument, если вектор нулевой.
Vector3 normalize(const Vector3& v);

// Угол между векторами в радианах [0, pi].
// Бросает std::invalid_argument, если хотя бы один вектор нулевой.
double angle(const Vector3& a, const Vector3& b);

} // namespace mylib