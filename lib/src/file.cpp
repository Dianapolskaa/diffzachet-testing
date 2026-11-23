#include "file.h"
#include <cmath>
#include <algorithm>

namespace mylib {

// ===== ВЕКТОР 2D =====
Vector2 add(const Vector2& a, const Vector2& b) {
    return {a.x + b.x, a.y + b.y};
}

Vector2 sub(const Vector2& a, const Vector2& b) {
    return {a.x - b.x, a.y - b.y};
}

double dot(const Vector2& a, const Vector2& b) {
    return a.x * b.x + a.y * b.y;
}

double cross(const Vector2& a, const Vector2& b) {
    return a.x * b.y - a.y * b.x;
}

double length(const Vector2& v) {
    return std::sqrt(v.x * v.x + v.y * v.y);
}

Vector2 normalize(const Vector2& v) {
    double len = length(v);
    if (len == 0.0) {
        throw std::invalid_argument("Cannot normalize zero vector");
    }
    return {v.x / len, v.y / len};
}

double angle(const Vector2& a, const Vector2& b) {
    double lenA = length(a);
    double lenB = length(b);
    if (lenA == 0.0 || lenB == 0.0) {
        throw std::invalid_argument("Cannot compute angle with zero vector");
    }
    double cosVal = dot(a, b) / (lenA * lenB);
    // Защита от выхода за [-1, 1] из-за ошибок плавающей точки
    cosVal = std::clamp(cosVal, -1.0, 1.0);
    return std::acos(cosVal);
}

// ===== ВЕКТОР 3D =====
Vector3 add(const Vector3& a, const Vector3& b) {
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

Vector3 sub(const Vector3& a, const Vector3& b) {
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}

double dot(const Vector3& a, const Vector3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 cross(const Vector3& a, const Vector3& b) {
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

double length(const Vector3& v) {
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vector3 normalize(const Vector3& v) {
    double len = length(v);
    if (len == 0.0) {
        throw std::invalid_argument("Cannot normalize zero vector");
    }
    return {v.x / len, v.y / len, v.z / len};
}

double angle(const Vector3& a, const Vector3& b) {
    double lenA = length(a);
    double lenB = length(b);
    if (lenA == 0.0 || lenB == 0.0) {
        throw std::invalid_argument("Cannot compute angle with zero vector");
    }
    double cosVal = dot(a, b) / (lenA * lenB);
    cosVal = std::clamp(cosVal, -1.0, 1.0);
    return std::acos(cosVal);
}

} // namespace mylib