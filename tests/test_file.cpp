#include "file.h"
#include <QtTest/QtTest>
#include <stdexcept>

using mylib::Date;
using mylib::DayOfWeek;

static bool sameDate(const Date& a, const Date& b) {
    return a.year == b.year && a.month == b.month && a.day == b.day;
}

class TestCalendar : public QObject
{
    Q_OBJECT

private slots:
    // isLeapYear
    void isLeapYear_divisibleBy4();
    void isLeapYear_divisibleBy100_notBy400();
    void isLeapYear_divisibleBy400();
    void isLeapYear_notDivisibleBy4();
    void isLeapYear_parameterized_data();
    void isLeapYear_parameterized();

    // daysInMonth
    void daysInMonth_february_leap();
    void daysInMonth_february_nonLeap();
    void daysInMonth_30_and_31();
    void daysInMonth_invalidMonth_throws();
    void daysInMonth_parameterized_data();
    void daysInMonth_parameterized();

    // isValidDate
    void isValidDate_valid();
    void isValidDate_invalidMonth();
    void isValidDate_invalidDay_feb29_nonLeap();
    void isValidDate_feb29_leap_valid();
    void isValidDate_zeroDay();

    // nextDay (граничные переходы)
    void nextDay_normal();
    void nextDay_endOfMonth();
    void nextDay_endOfFebruary_leap();
    void nextDay_endOfFebruary_nonLeap();
    void nextDay_endOfYear();
    void nextDay_invalid_throws();

    // daysBetween
    void daysBetween_sameDate_zero();
    void daysBetween_consecutiveDays();
    void daysBetween_reverseOrder_negative();
    void daysBetween_fullYear_nonLeap();
    void daysBetween_fullYear_leap();
    void daysBetween_invalid_throws();

    // dayOfWeek (проверено на известных датах)
    void dayOfWeek_2026_11_24_tuesday();
    void dayOfWeek_2000_01_01_saturday();
    void dayOfWeek_0001_01_01_monday();
    void dayOfWeek_invalid_throws();
};

// ===== isLeapYear =====
void TestCalendar::isLeapYear_divisibleBy4() {
    QVERIFY(mylib::isLeapYear(2024));
}

void TestCalendar::isLeapYear_divisibleBy100_notBy400() {
    QVERIFY(!mylib::isLeapYear(1900)); // Классическая ловушка!
    QVERIFY(!mylib::isLeapYear(2100));
}

void TestCalendar::isLeapYear_divisibleBy400() {
    QVERIFY(mylib::isLeapYear(2000));
    QVERIFY(mylib::isLeapYear(1600));
}

void TestCalendar::isLeapYear_notDivisibleBy4() {
    QVERIFY(!mylib::isLeapYear(2023));
}

void TestCalendar::isLeapYear_parameterized_data() {
    QTest::addColumn<int>("year");
    QTest::addColumn<bool>("expected");

    QTest::newRow("2024") << 2024 << true;
    QTest::newRow("2023") << 2023 << false;
    QTest::newRow("1900") << 1900 << false;
    QTest::newRow("2000") << 2000 << true;
    QTest::newRow("2100") << 2100 << false;
    QTest::newRow("4")    << 4    << true;
}

void TestCalendar::isLeapYear_parameterized() {
    QFETCH(int, year);
    QFETCH(bool, expected);
    QCOMPARE(mylib::isLeapYear(year), expected);
}

// ===== daysInMonth =====
void TestCalendar::daysInMonth_february_leap() {
    QCOMPARE(mylib::daysInMonth(2024, 2), 29);
    QCOMPARE(mylib::daysInMonth(2000, 2), 29);
}

void TestCalendar::daysInMonth_february_nonLeap() {
    QCOMPARE(mylib::daysInMonth(2023, 2), 28);
    QCOMPARE(mylib::daysInMonth(1900, 2), 28); // 1900 не високосный!
}

void TestCalendar::daysInMonth_30_and_31() {
    QCOMPARE(mylib::daysInMonth(2026, 1), 31);
    QCOMPARE(mylib::daysInMonth(2026, 4), 30);
    QCOMPARE(mylib::daysInMonth(2026, 12), 31);
}

void TestCalendar::daysInMonth_invalidMonth_throws() {
    QVERIFY_EXCEPTION_THROWN(mylib::daysInMonth(2026, 0), std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN(mylib::daysInMonth(2026, 13), std::invalid_argument);
}

void TestCalendar::daysInMonth_parameterized_data() {
    QTest::addColumn<int>("year");
    QTest::addColumn<int>("month");
    QTest::addColumn<int>("expected");

    QTest::newRow("feb_leap")    << 2024 << 2 << 29;
    QTest::newRow("feb_nonleap") << 2023 << 2 << 28;
    QTest::newRow("jan")         << 2026 << 1 << 31;
    QTest::newRow("jun")         << 2026 << 6 << 30;
    QTest::newRow("dec")         << 2026 << 12 << 31;
}

void TestCalendar::daysInMonth_parameterized() {
    QFETCH(int, year);
    QFETCH(int, month);
    QFETCH(int, expected);
    QCOMPARE(mylib::daysInMonth(year, month), expected);
}

// ===== isValidDate =====
void TestCalendar::isValidDate_valid() {
    QVERIFY(mylib::isValidDate({2026, 11, 24}));
    QVERIFY(mylib::isValidDate({2000, 2, 29}));
}

void TestCalendar::isValidDate_invalidMonth() {
    QVERIFY(!mylib::isValidDate({2026, 13, 1}));
    QVERIFY(!mylib::isValidDate({2026, 0, 1}));
}

void TestCalendar::isValidDate_invalidDay_feb29_nonLeap() {
    QVERIFY(!mylib::isValidDate({2023, 2, 29})); // 2023 не високосный
    QVERIFY(!mylib::isValidDate({2026, 4, 31})); // В апреле 30 дней
}

void TestCalendar::isValidDate_feb29_leap_valid() {
    QVERIFY(mylib::isValidDate({2024, 2, 29}));
}

void TestCalendar::isValidDate_zeroDay() {
    QVERIFY(!mylib::isValidDate({2026, 1, 0}));
}

// ===== nextDay =====
void TestCalendar::nextDay_normal() {
    auto res = mylib::nextDay({2026, 11, 24});
    QVERIFY(sameDate(res, {2026, 11, 25}));
}

void TestCalendar::nextDay_endOfMonth() {
    auto res = mylib::nextDay({2026, 11, 30});
    QVERIFY(sameDate(res, {2026, 12, 1}));
}

void TestCalendar::nextDay_endOfFebruary_leap() {
    auto res = mylib::nextDay({2024, 2, 28});
    QVERIFY(sameDate(res, {2024, 2, 29}));
    auto res2 = mylib::nextDay({2024, 2, 29});
    QVERIFY(sameDate(res2, {2024, 3, 1}));
}

void TestCalendar::nextDay_endOfFebruary_nonLeap() {
    auto res = mylib::nextDay({2023, 2, 28});
    QVERIFY(sameDate(res, {2023, 3, 1}));
}

void TestCalendar::nextDay_endOfYear() {
    auto res = mylib::nextDay({2026, 12, 31});
    QVERIFY(sameDate(res, {2027, 1, 1}));
}

void TestCalendar::nextDay_invalid_throws() {
    QVERIFY_EXCEPTION_THROWN(mylib::nextDay({2026, 2, 30}), std::invalid_argument);
}

// ===== daysBetween =====
void TestCalendar::daysBetween_sameDate_zero() {
    Date d{2026, 11, 24};
    QCOMPARE(mylib::daysBetween(d, d), 0);
}

void TestCalendar::daysBetween_consecutiveDays() {
    QCOMPARE(mylib::daysBetween({2026, 11, 23}, {2026, 11, 24}), 1);
}

void TestCalendar::daysBetween_reverseOrder_negative() {
    QCOMPARE(mylib::daysBetween({2026, 11, 24}, {2026, 11, 23}), -1);
}

void TestCalendar::daysBetween_fullYear_nonLeap() {
    // 2026 не високосный: от 1 янв до 31 дек = 364 дня
    QCOMPARE(mylib::daysBetween({2026, 1, 1}, {2026, 12, 31}), 364);
    // От 1 янв 2026 до 1 янв 2027 = 365
    QCOMPARE(mylib::daysBetween({2026, 1, 1}, {2027, 1, 1}), 365);
}

void TestCalendar::daysBetween_fullYear_leap() {
    // 2024 високосный: от 1 янв 2024 до 1 янв 2025 = 366
    QCOMPARE(mylib::daysBetween({2024, 1, 1}, {2025, 1, 1}), 366);
    // Через 29 февраля
    QCOMPARE(mylib::daysBetween({2024, 2, 28}, {2024, 3, 1}), 2);
}

void TestCalendar::daysBetween_invalid_throws() {
    QVERIFY_EXCEPTION_THROWN(
        mylib::daysBetween({2026, 13, 1}, {2026, 1, 1}), std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN(
        mylib::daysBetween({2026, 1, 1}, {2026, 2, 30}), std::invalid_argument);
}

// ===== dayOfWeek =====
void TestCalendar::dayOfWeek_2026_11_24_tuesday() {
    QCOMPARE(static_cast<int>(mylib::dayOfWeek({2026, 11, 24})),
             static_cast<int>(DayOfWeek::Tuesday));
}

void TestCalendar::dayOfWeek_2000_01_01_saturday() {
    QCOMPARE(static_cast<int>(mylib::dayOfWeek({2000, 1, 1})),
             static_cast<int>(DayOfWeek::Saturday));
}

void TestCalendar::dayOfWeek_0001_01_01_monday() {
    QCOMPARE(static_cast<int>(mylib::dayOfWeek({1, 1, 1})),
             static_cast<int>(DayOfWeek::Monday));
}

void TestCalendar::dayOfWeek_invalid_throws() {
    QVERIFY_EXCEPTION_THROWN(mylib::dayOfWeek({2026, 4, 31}), std::invalid_argument);
}

QTEST_MAIN(TestCalendar)
#include "test_file.moc"