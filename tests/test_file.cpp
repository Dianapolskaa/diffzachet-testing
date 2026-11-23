#include "file.h"
#include <QtTest/QtTest>
#include <stdexcept>

class TestRational : public QObject
{
    Q_OBJECT

private slots:
    // Конструктор и нормализация
    void constructor_basic();
    void constructor_negativeDenominator();
    void constructor_zeroDenominator_throws();
    void constructor_simplification();

    // Арифметические операции
    void add_basic();
    void sub_basic();
    void mul_basic();
    void div_basic();
    void div_byZero_throws();

    // Сравнение (параметризованный тест)
    void compare_equal_data();
    void compare_equal();
    void compare_less();

    // Строковое представление
    void toString_properFraction();
    void toString_improperFraction();
    void toString_integer();
    void toString_negative();

    // Параметризованный тест на операции
    void arithmetic_data();
    void arithmetic();
};

// --- Конструктор ---
void TestRational::constructor_basic() {
    mylib::Rational r(1, 2);
    QCOMPARE(r.numerator(), 1LL);
    QCOMPARE(r.denominator(), 2LL);
}

void TestRational::constructor_negativeDenominator() {
    mylib::Rational r(1, -2);
    QCOMPARE(r.numerator(), -1LL);
    QCOMPARE(r.denominator(), 2LL);
}

void TestRational::constructor_zeroDenominator_throws() {
    QVERIFY_EXCEPTION_THROWN(mylib::Rational(1, 0), std::invalid_argument);
}

void TestRational::constructor_simplification() {
    mylib::Rational r(4, 8);
    QCOMPARE(r.numerator(), 1LL);
    QCOMPARE(r.denominator(), 2LL);
}

// --- Арифметика ---
void TestRational::add_basic() {
    mylib::Rational r1(1, 2);
    mylib::Rational r2(1, 3);
    mylib::Rational res = r1 + r2;
    QCOMPARE(res.numerator(), 5LL);
    QCOMPARE(res.denominator(), 6LL);
}

void TestRational::sub_basic() {
    mylib::Rational r1(1, 2);
    mylib::Rational r2(1, 3);
    mylib::Rational res = r1 - r2;
    QCOMPARE(res.numerator(), 1LL);
    QCOMPARE(res.denominator(), 6LL);
}

void TestRational::mul_basic() {
    mylib::Rational r1(1, 2);
    mylib::Rational r2(2, 3);
    mylib::Rational res = r1 * r2;
    QCOMPARE(res.numerator(), 1LL);
    QCOMPARE(res.denominator(), 3LL);
}

void TestRational::div_basic() {
    mylib::Rational r1(1, 2);
    mylib::Rational r2(2, 3);
    mylib::Rational res = r1 / r2;
    QCOMPARE(res.numerator(), 3LL);
    QCOMPARE(res.denominator(), 4LL);
}

void TestRational::div_byZero_throws() {
    mylib::Rational r1(1, 2);
    mylib::Rational r2(0, 1);
    QVERIFY_EXCEPTION_THROWN(r1 / r2, std::invalid_argument);
}

// --- Сравнение ---
void TestRational::compare_equal_data() {
    QTest::addColumn<long long>("n1");
    QTest::addColumn<long long>("d1");
    QTest::addColumn<long long>("n2");
    QTest::addColumn<long long>("d2");

    QTest::newRow("1/2 == 2/4") << 1LL << 2LL << 2LL << 4LL;
    QTest::newRow("-1/2 == 1/-2") << -1LL << 2LL << 1LL << -2LL;
    QTest::newRow("0/1 == 0/5") << 0LL << 1LL << 0LL << 5LL;
}

void TestRational::compare_equal() {
    QFETCH(long long, n1);
    QFETCH(long long, d1);
    QFETCH(long long, n2);
    QFETCH(long long, d2);

    QVERIFY(mylib::Rational(n1, d1) == mylib::Rational(n2, d2));
}

void TestRational::compare_less() {
    QVERIFY(mylib::Rational(1, 3) < mylib::Rational(1, 2));
    QVERIFY(mylib::Rational(-1, 2) < mylib::Rational(1, 2));
}

// --- toString ---
void TestRational::toString_properFraction() {
    QCOMPARE(mylib::Rational(1, 2).toString(), std::string("1/2"));
}

void TestRational::toString_improperFraction() {
    QCOMPARE(mylib::Rational(5, 2).toString(), std::string("5/2"));
}

void TestRational::toString_integer() {
    QCOMPARE(mylib::Rational(4, 2).toString(), std::string("2"));
}

void TestRational::toString_negative() {
    QCOMPARE(mylib::Rational(-1, 2).toString(), std::string("-1/2"));
}

// --- Параметризованный тест на операции ---
void TestRational::arithmetic_data() {
    QTest::addColumn<mylib::Rational>("a");
    QTest::addColumn<mylib::Rational>("b");
    QTest::addColumn<mylib::Rational>("sum");
    QTest::addColumn<mylib::Rational>("diff");

    QTest::newRow("simple")
        << mylib::Rational(1, 4)
        << mylib::Rational(1, 4)
        << mylib::Rational(1, 2)
        << mylib::Rational(0, 1);

    QTest::newRow("different_denoms")
        << mylib::Rational(2, 3)
        << mylib::Rational(1, 6)
        << mylib::Rational(5, 6)
        << mylib::Rational(1, 2);
}

void TestRational::arithmetic() {
    QFETCH(mylib::Rational, a);
    QFETCH(mylib::Rational, b);
    QFETCH(mylib::Rational, sum);
    QFETCH(mylib::Rational, diff);

    QCOMPARE(a + b, sum);
    QCOMPARE(a - b, diff);
}

QTEST_MAIN(TestRational)
#include "test_file.moc"