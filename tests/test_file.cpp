#include "file.h"
#include <QtTest/QtTest>
#include <cmath>
#include <stdexcept>

class TestComplex : public QObject
{
    Q_OBJECT

private slots:
    // Конструктор и геттеры
    void constructor_default();
    void constructor_withValues();

    // Сложение и вычитание
    void add_basic();
    void add_withZero();
    void sub_basic();

    // Умножение
    void mul_basic();
    void mul_imaginaryUnit(); // i * i = -1
    void mul_byZero();

    // Деление
    void div_basic();
    void div_byZero_throws();

    // Сопряжение
    void conjugate_basic();
    void conjugate_realOnly();

    // Модуль
    void modulus_basic();
    void modulus_zero();
    void modulus_imaginaryOnly();

    // Возведение в степень
    void power_zero();
    void power_one();
    void power_two();
    void power_negative();
    void power_zeroToNegative_throws();

    // Сравнение
    void equality();
    void inequality();

    // toString
    void toString_basic();
    void toString_realOnly();
    void toString_imaginaryOnly();

    // Параметризованные тесты
    void add_parameterized_data();
    void add_parameterized();
    void mul_parameterized_data();
    void mul_parameterized();
};

// --- Конструктор ---
void TestComplex::constructor_default() {
    mylib::Complex c;
    QCOMPARE(c.real(), 0.0);
    QCOMPARE(c.imag(), 0.0);
}

void TestComplex::constructor_withValues() {
    mylib::Complex c(3.0, -4.0);
    QCOMPARE(c.real(), 3.0);
    QCOMPARE(c.imag(), -4.0);
}

// --- Сложение/вычитание ---
void TestComplex::add_basic() {
    mylib::Complex a(1.0, 2.0);
    mylib::Complex b(3.0, 4.0);
    mylib::Complex res = a + b;
    QCOMPARE(res.real(), 4.0);
    QCOMPARE(res.imag(), 6.0);
}

void TestComplex::add_withZero() {
    mylib::Complex a(5.0, -3.0);
    mylib::Complex b(0.0, 0.0);
    QCOMPARE((a + b).real(), 5.0);
    QCOMPARE((a + b).imag(), -3.0);
}

void TestComplex::sub_basic() {
    mylib::Complex a(5.0, 7.0);
    mylib::Complex b(2.0, 3.0);
    mylib::Complex res = a - b;
    QCOMPARE(res.real(), 3.0);
    QCOMPARE(res.imag(), 4.0);
}

// --- Умножение ---
void TestComplex::mul_basic() {
    mylib::Complex a(2.0, 3.0);
    mylib::Complex b(1.0, 4.0);
    // (2+3i)(1+4i) = 2+8i+3i+12i² = 2+11i-12 = -10+11i
    mylib::Complex res = a * b;
    QCOMPARE(res.real(), -10.0);
    QCOMPARE(res.imag(), 11.0);
}

void TestComplex::mul_imaginaryUnit() {
    // i * i = -1
    mylib::Complex i(0.0, 1.0);
    mylib::Complex res = i * i;
    QCOMPARE(res.real(), -1.0);
    QCOMPARE(res.imag(), 0.0);
}

void TestComplex::mul_byZero() {
    mylib::Complex a(5.0, 3.0);
    mylib::Complex zero(0.0, 0.0);
    mylib::Complex res = a * zero;
    QCOMPARE(res.real(), 0.0);
    QCOMPARE(res.imag(), 0.0);
}

// --- Деление ---
void TestComplex::div_basic() {
    mylib::Complex a(1.0, 2.0);
    mylib::Complex b(1.0, 1.0);
    // (1+2i)/(1+i) = (1+2i)(1-i)/((1+i)(1-i)) = (1-i+2i-2i²)/(1+1) = (3+i)/2 = 1.5+0.5i
    mylib::Complex res = a / b;
    QVERIFY(std::abs(res.real() - 1.5) < 1e-9);
    QVERIFY(std::abs(res.imag() - 0.5) < 1e-9);
}

void TestComplex::div_byZero_throws() {
    mylib::Complex a(1.0, 2.0);
    mylib::Complex zero(0.0, 0.0);
    QVERIFY_EXCEPTION_THROWN(a / zero, std::invalid_argument);
}

// --- Сопряжение ---
void TestComplex::conjugate_basic() {
    mylib::Complex c(3.0, -4.0);
    mylib::Complex conj = c.conjugate();
    QCOMPARE(conj.real(), 3.0);
    QCOMPARE(conj.imag(), 4.0);
}

void TestComplex::conjugate_realOnly() {
    mylib::Complex c(5.0, 0.0);
    mylib::Complex conj = c.conjugate();
    QCOMPARE(conj.real(), 5.0);
    QCOMPARE(conj.imag(), 0.0);
}

// --- Модуль ---
void TestComplex::modulus_basic() {
    mylib::Complex c(3.0, 4.0);
    QCOMPARE(c.modulus(), 5.0); // 3-4-5 треугольник
}

void TestComplex::modulus_zero() {
    mylib::Complex c(0.0, 0.0);
    QCOMPARE(c.modulus(), 0.0);
}

void TestComplex::modulus_imaginaryOnly() {
    mylib::Complex c(0.0, -7.0);
    QCOMPARE(c.modulus(), 7.0);
}

// --- Возведение в степень ---
void TestComplex::power_zero() {
    mylib::Complex c(5.0, 3.0);
    mylib::Complex res = c.power(0);
    QCOMPARE(res.real(), 1.0);
    QCOMPARE(res.imag(), 0.0);
}

void TestComplex::power_one() {
    mylib::Complex c(2.0, 3.0);
    mylib::Complex res = c.power(1);
    QCOMPARE(res.real(), 2.0);
    QCOMPARE(res.imag(), 3.0);
}

void TestComplex::power_two() {
    mylib::Complex c(1.0, 1.0);
    // (1+i)² = 1+2i+i² = 2i
    mylib::Complex res = c.power(2);
    QVERIFY(std::abs(res.real()) < 1e-9);
    QVERIFY(std::abs(res.imag() - 2.0) < 1e-9);
}

void TestComplex::power_negative() {
    mylib::Complex i(0.0, 1.0);
    // i^(-1) = 1/i = -i
    mylib::Complex res = i.power(-1);
    QVERIFY(std::abs(res.real()) < 1e-9);
    QVERIFY(std::abs(res.imag() - (-1.0)) < 1e-9);
}

void TestComplex::power_zeroToNegative_throws() {
    mylib::Complex zero(0.0, 0.0);
    QVERIFY_EXCEPTION_THROWN(zero.power(-2), std::invalid_argument);
}

// --- Сравнение ---
void TestComplex::equality() {
    mylib::Complex a(1.0, 2.0);
    mylib::Complex b(1.0, 2.0);
    QVERIFY(a == b);
}

void TestComplex::inequality() {
    mylib::Complex a(1.0, 2.0);
    mylib::Complex b(1.0, 3.0);
    QVERIFY(a != b);
}

// --- toString ---
void TestComplex::toString_basic() {
    mylib::Complex c(3.0, 4.0);
    QCOMPARE(c.toString(), std::string("3.00+4.00i"));
}

void TestComplex::toString_realOnly() {
    mylib::Complex c(5.0, 0.0);
    QCOMPARE(c.toString(), std::string("5.00"));
}

void TestComplex::toString_imaginaryOnly() {
    mylib::Complex c(0.0, -2.0);
    QCOMPARE(c.toString(), std::string("-2.00i"));
}

// --- Параметризованные тесты ---
void TestComplex::add_parameterized_data() {
    QTest::addColumn<double>("a_real");
    QTest::addColumn<double>("a_imag");
    QTest::addColumn<double>("b_real");
    QTest::addColumn<double>("b_imag");
    QTest::addColumn<double>("exp_real");
    QTest::addColumn<double>("exp_imag");

    QTest::newRow("positive") << 1.0 << 2.0 << 3.0 << 4.0 << 4.0 << 6.0;
    QTest::newRow("negative") << -1.0 << -2.0 << 1.0 << 2.0 << 0.0 << 0.0;
    QTest::newRow("mixed") << 5.0 << -3.0 << -2.0 << 7.0 << 3.0 << 4.0;
}

void TestComplex::add_parameterized() {
    QFETCH(double, a_real);
    QFETCH(double, a_imag);
    QFETCH(double, b_real);
    QFETCH(double, b_imag);
    QFETCH(double, exp_real);
    QFETCH(double, exp_imag);

    mylib::Complex a(a_real, a_imag);
    mylib::Complex b(b_real, b_imag);
    mylib::Complex res = a + b;

    QCOMPARE(res.real(), exp_real);
    QCOMPARE(res.imag(), exp_imag);
}

void TestComplex::mul_parameterized_data() {
    QTest::addColumn<double>("a_real");
    QTest::addColumn<double>("a_imag");
    QTest::addColumn<double>("b_real");
    QTest::addColumn<double>("b_imag");
    QTest::addColumn<double>("exp_real");
    QTest::addColumn<double>("exp_imag");

    QTest::newRow("i*i") << 0.0 << 1.0 << 0.0 << 1.0 << -1.0 << 0.0;
    QTest::newRow("real*real") << 2.0 << 0.0 << 3.0 << 0.0 << 6.0 << 0.0;
    QTest::newRow("complex") << 1.0 << 1.0 << 1.0 << -1.0 << 2.0 << 0.0; // (1+i)(1-i) = 2
}

void TestComplex::mul_parameterized() {
    QFETCH(double, a_real);
    QFETCH(double, a_imag);
    QFETCH(double, b_real);
    QFETCH(double, b_imag);
    QFETCH(double, exp_real);
    QFETCH(double, exp_imag);

    mylib::Complex a(a_real, a_imag);
    mylib::Complex b(b_real, b_imag);
    mylib::Complex res = a * b;

    QCOMPARE(res.real(), exp_real);
    QCOMPARE(res.imag(), exp_imag);
}

QTEST_MAIN(TestComplex)
#include "test_file.moc"