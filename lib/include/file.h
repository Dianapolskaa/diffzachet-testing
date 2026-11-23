#pragma once
#include <stdexcept>

namespace mylib {

struct Date {
    int year;
    int month; // 1..12
    int day;   // 1..daysInMonth(year, month)
};

enum class DayOfWeek {
    Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday
};

// Високосный ли год (григорианский календарь):
// делится на 4, но не на 100, либо делится на 400.
bool isLeapYear(int year);

// Количество дней в месяце. Бросает std::invalid_argument, если month вне [1, 12].
int daysInMonth(int year, int month);

// Валидна ли дата (год >= 1, месяц 1..12, день в пределах месяца).
bool isValidDate(const Date& d);

// Следующий день. Бросает std::invalid_argument, если дата невалидна.
Date nextDay(const Date& d);

// Разница в днях: (b - a). Знак учитывается (может быть отрицательным).
// Бросает std::invalid_argument, если хотя бы одна дата невалидна.
int daysBetween(const Date& a, const Date& b);

// День недели. Поддерживаются даты от 0001-01-01 (понедельник).
// Бросает std::invalid_argument, если дата невалидна.
DayOfWeek dayOfWeek(const Date& d);

} // namespace mylib