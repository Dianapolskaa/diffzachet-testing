#pragma once

namespace mylib {

struct Rectangle {
    double x;      // Координата X левого верхнего угла
    double y;      // Координата Y левого верхнего угла
    double width;  // Ширина
    double height; // Высота
};

// Вычисляет площадь прямоугольника.
// Если width < 0 или height < 0, возвращает 0.0.
double area(const Rectangle& r);

// Проверяет, принадлежит ли точка (px, py) прямоугольнику.
// Точки на границе считаются принадлежащими.
// Если у прямоугольника отрицательные размеры, возвращает false.
bool contains(const Rectangle& r, double px, double py);

// Проверяет, пересекаются ли два прямоугольника.
// ВАЖНО: Касание краем (площадь пересечения = 0) НЕ считается пересечением.
bool intersects(const Rectangle& a, const Rectangle& b);

// Вычисляет прямоугольник, охватывающий оба исходных (bounding box).
// Корректно работает с прямоугольниками, имеющими отрицательные размеры.
Rectangle boundingBox(const Rectangle& a, const Rectangle& b);

// Вычисляет прямоугольник пересечения.
// Возвращает true, если пересечение существует (площадь строго > 0), и записывает результат в out.
// Если пересечения нет (или только касание), возвращает false.
bool getIntersection(const Rectangle& a, const Rectangle& b, Rectangle& out);

} // namespace mylib