#include "file.h"
#include <algorithm>

namespace mylib {

double area(const Rectangle& r) {
    if (r.width < 0.0 || r.height < 0.0) {
        return 0.0;
    }
    return r.width * r.height;
}

bool contains(const Rectangle& r, double px, double py) {
    if (r.width < 0.0 || r.height < 0.0) {
        return false;
    }
    return px >= r.x && px <= r.x + r.width &&
           py >= r.y && py <= r.y + r.height;
}

bool intersects(const Rectangle& a, const Rectangle& b) {
    if (a.width < 0.0 || a.height < 0.0 || b.width < 0.0 || b.height < 0.0) {
        return false;
    }
    // Строгое пересечение: касание краем (например, a.x + a.width == b.x) вернет false
    return a.x < b.x + b.width &&
           a.x + a.width > b.x &&
           a.y < b.y + b.height &&
           a.y + a.height > b.y;
}

Rectangle boundingBox(const Rectangle& a, const Rectangle& b) {
    // Нормализуем размеры на случай отрицательных значений
    auto norm = [](const Rectangle& r) -> Rectangle {
        double w = r.width < 0.0 ? 0.0 : r.width;
        double h = r.height < 0.0 ? 0.0 : r.height;
        return {r.x, r.y, w, h};
    };

    Rectangle na = norm(a);
    Rectangle nb = norm(b);

    double minX = std::min(na.x, nb.x);
    double minY = std::min(na.y, nb.y);
    double maxX = std::max(na.x + na.width, nb.x + nb.width);
    double maxY = std::max(na.y + na.height, nb.y + nb.height);

    return {minX, minY, maxX - minX, maxY - minY};
}

bool getIntersection(const Rectangle& a, const Rectangle& b, Rectangle& out) {
    if (!intersects(a, b)) {
        return false;
    }

    double left = std::max(a.x, b.x);
    double right = std::min(a.x + a.width, b.x + b.width);
    double top = std::max(a.y, b.y);
    double bottom = std::min(a.y + a.height, b.y + b.height);

    out = {left, top, right - left, bottom - top};
    return true;
}

} // namespace mylib