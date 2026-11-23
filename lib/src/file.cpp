#include "file.h"

namespace mylib {

namespace {
// Накопительные дни до начала месяца (индекс 0 = до января)
constexpr int daysBeforeMonth[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

// Число дней от 0001-01-01 (понедельник). Вызывается только для валидных дат.
long long totalDays(const Date& d) {
    long long y = d.year - 1;
    long long days = 365 * y + y / 4 - y / 100 + y / 400;
    days += daysBeforeMonth[d.month - 1];
    if (d.month > 2 && isLeapYear(d.year)) {
        days += 1;
    }
    days += d.day - 1;
    return days;
}
} // namespace

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int daysInMonth(int year, int month) {
    if (month < 1 || month > 12) {
        throw std::invalid_argument("Month must be in range [1, 12]");
    }
    static const int md[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year)) {
        return 29;
    }
    return md[month - 1];
}

bool isValidDate(const Date& d) {
    if (d.year < 1) return false;
    if (d.month < 1 || d.month > 12) return false;
    if (d.day < 1 || d.day > daysInMonth(d.year, d.month)) return false;
    return true;
}

Date nextDay(const Date& d) {
    if (!isValidDate(d)) {
        throw std::invalid_argument("Invalid date");
    }
    Date res = d;
    int dim = daysInMonth(d.year, d.month);
    if (d.day < dim) {
        res.day = d.day + 1;
    } else if (d.month < 12) {
        res.day = 1;
        res.month = d.month + 1;
    } else {
        res.day = 1;
        res.month = 1;
        res.year = d.year + 1;
    }
    return res;
}

int daysBetween(const Date& a, const Date& b) {
    if (!isValidDate(a) || !isValidDate(b)) {
        throw std::invalid_argument("Invalid date");
    }
    return static_cast<int>(totalDays(b) - totalDays(a));
}

DayOfWeek dayOfWeek(const Date& d) {
    if (!isValidDate(d)) {
        throw std::invalid_argument("Invalid date");
    }
    long long t = totalDays(d);
    int idx = static_cast<int>(((t % 7) + 7) % 7); // 0 = Monday
    return static_cast<DayOfWeek>(idx);
}

} // namespace mylib