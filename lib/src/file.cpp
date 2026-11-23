#include "file.h"
#include <cmath>
#include <algorithm>

namespace mylib {

bool exists(double a, double b, double c) {
    if (a <= 0.0 || b <= 0.0 || c <= 0.0) {
        return false;
    }
    return (a + b > c) && (a + c > b) && (b + c > a);
}

TriangleType typeBySides(double a, double b, double c) {
    if (!exists(a, b, c)) {
        return TriangleType::Invalid;
    }
    
    const double eps = 1e-9;
    bool eq_ab = std::abs(a - b) < eps;
    bool eq_ac = std::abs(a - c) < eps;
    bool eq_bc = std::abs(b - c) < eps;
    
    if (eq_ab && eq_ac) {
        return TriangleType::Equilateral;
    }
    if (eq_ab || eq_ac || eq_bc) {
        return TriangleType::Isosceles;
    }
    return TriangleType::Scalene;
}

AngleType typeByAngles(double a, double b, double c) {
    if (!exists(a, b, c)) {
        return AngleType::Invalid;
    }
    
    // Сортируем стороны, чтобы c всегда была наибольшей (гипотенузой или стороной против наибольшего угла).
    // Это гарантирует, что порядок ввода сторон не влияет на результат.
    double sides[3] = {a, b, c};
    std::sort(sides, sides + 3);
    a = sides[0];
    b = sides[1];
    c = sides[2];
    
    const double eps = 1e-9;
    double a2 = a * a;
    double b2 = b * b;
    double c2 = c * c;
    
    double sum = a2 + b2;
    if (std::abs(sum - c2) < eps) {
        return AngleType::Right;
    }
    if (sum > c2) {
        return AngleType::Acute;
    }
    return AngleType::Obtuse;
}

double area(double a, double b, double c) {
    if (!exists(a, b, c)) {
        return -1.0;
    }
    
    double p = (a + b + c) / 2.0;
    return std::sqrt(p * (p - a) * (p - b) * (p - c));
}

} // namespace mylib
