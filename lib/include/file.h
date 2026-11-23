#pragma once

namespace mylib {

enum class RootCount {
    None,       // Нет действительных корней
    One,        // Один корень (или линейное уравнение)
    Two,        // Два различных корня
    Infinite    // Бесконечно много корней (тождество 0 = 0)
};

// Решает уравнение ax^2 + bx + c = 0.
// Если a == 0, уравнение вырождается в линейное bx + c = 0.
// Возвращает количество корней. Значения корней записываются в x1 и x2.
// Для RootCount::One корень записывается в x1.
// Для RootCount::None или Infinite значения x1 и x2 не изменяются.
RootCount solveQuadratic(double a, double b, double c, double& x1, double& x2);

} // namespace mylib