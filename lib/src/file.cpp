#include "file.h"
#include <cmath>

namespace mylib {

RootCount solveQuadratic(double a, double b, double c, double& x1, double& x2) {
    const double eps = 1e-9;

    // Вырожденный случай: a == 0 (линейное уравнение или константа)
    if (std::abs(a) <= eps) {
        if (std::abs(b) <= eps) {
            if (std::abs(c) <= eps) {
                return RootCount::Infinite; // 0 = 0
            }
            return RootCount::None; // c = 0, где c != 0 (например, 5 = 0)
        }
        // Линейное уравнение bx + c = 0
        x1 = -c / b;
        return RootCount::One;
    }

    // Полноценное квадратное уравнение
    double discriminant = b * b - 4.0 * a * c;

    if (discriminant > eps) {
        double sqrtD = std::sqrt(discriminant);
        x1 = (-b + sqrtD) / (2.0 * a);
        x2 = (-b - sqrtD) / (2.0 * a);
        return RootCount::Two;
    } else if (discriminant < -eps) {
        return RootCount::None;
    } else {
        // D == 0 (один корень кратности 2)
        x1 = -b / (2.0 * a);
        return RootCount::One;
    }
}

} // namespace mylib