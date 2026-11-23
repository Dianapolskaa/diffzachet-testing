#include "file.h"
#include <QtTest/QtTest>
#include <cmath>
#include <stdexcept>

static const double EPS = 1e-9;

class TestVector : public QObject
{
    Q_OBJECT

private slots:
    // ===== 2D =====
    void add2D_basic();
    void sub2D_basic();
    void dot2D_perpendicular_zero();
    void dot2D_parallel_positive();
    void cross2D_basic();
    void cross2D_anticommutative();
    void length2D_pythagorean();
    void length2D_zero();
    void normalize2D_unitLength();
    void normalize2D_zeroVector_throws();
    void angle2D_perpendicular_piOver2();
    void angle2D_parallel_zero();
    void angle2D_antiparallel_pi();
    void angle2D_zeroVector_throws();

    // ===== 3D =====
    void add3D_basic();
    void dot3D_basic();
    void cross3D_basisVectors();
    void cross3D_parallel_zero();
    void length3D_basic();
    void normalize3D_unitLength();
    void normalize3D_zeroVector_throws();
    void angle3D_parallel_zero();

    // Параметризованный тест (dot product 2D)
    void dot2D_parameterized_data();
    void dot2D_parameterized();
};

// ===== 2D =====
void TestVector::add2D_basic() {
    auto res = mylib::add(mylib::Vector2{1.0, 2.0}, mylib::Vector2{3.0, 4.0});
    QCOMPARE(res.x, 4.0);
    QCOMPARE(res.y, 6.0);
}

void TestVector::sub2D_basic() {
    auto res = mylib::sub(mylib::Vector2{5.0, 7.0}, mylib::Vector2{2.0, 3.0});
    QCOMPARE(res.x, 3.0);
    QCOMPARE(res.y, 4.0);
}

void TestVector::dot2D_perpendicular_zero() {
    QCOMPARE(mylib::dot(mylib::Vector2{1.0, 0.0}, mylib::Vector2{0.0, 1.0}), 0.0);
}

void TestVector::dot2D_parallel_positive() {
    QCOMPARE(mylib::dot(mylib::Vector2{2.0, 0.0}, mylib::Vector2{3.0, 0.0}), 6.0);
}

void TestVector::cross2D_basic() {
    QCOMPARE(mylib::cross(mylib::Vector2{1.0, 0.0}, mylib::Vector2{0.0, 1.0}), 1.0);
}

void TestVector::cross2D_anticommutative() {
    double ab = mylib::cross(mylib::Vector2{2.0, 3.0}, mylib::Vector2{4.0, 5.0});
    double ba = mylib::cross(mylib::Vector2{4.0, 5.0}, mylib::Vector2{2.0, 3.0});
    QVERIFY(std::abs(ab + ba) < EPS);
}

void TestVector::length2D_pythagorean() {
    QCOMPARE(mylib::length(mylib::Vector2{3.0, 4.0}), 5.0);
}

void TestVector::length2D_zero() {
    QCOMPARE(mylib::length(mylib::Vector2{0.0, 0.0}), 0.0);
}

void TestVector::normalize2D_unitLength() {
    auto n = mylib::normalize(mylib::Vector2{3.0, 4.0});
    QVERIFY(std::abs(mylib::length(n) - 1.0) < EPS);
    QVERIFY(std::abs(n.x - 0.6) < EPS);
    QVERIFY(std::abs(n.y - 0.8) < EPS);
}

void TestVector::normalize2D_zeroVector_throws() {
    QVERIFY_EXCEPTION_THROWN(mylib::normalize(mylib::Vector2{0.0, 0.0}), std::invalid_argument);
}

void TestVector::angle2D_perpendicular_piOver2() {
    double a = mylib::angle(mylib::Vector2{1.0, 0.0}, mylib::Vector2{0.0, 1.0});
    QVERIFY(std::abs(a - M_PI / 2.0) < EPS);
}

void TestVector::angle2D_parallel_zero() {
    double a = mylib::angle(mylib::Vector2{2.0, 2.0}, mylib::Vector2{4.0, 4.0});
    // Без clamp здесь может быть NaN из-за 1.0000000001
    QVERIFY(std::abs(a) < 1e-6); // Используем более мягкий эпсилон
}

void TestVector::angle2D_antiparallel_pi() {
    double a = mylib::angle(mylib::Vector2{1.0, 0.0}, mylib::Vector2{-1.0, 0.0});
    QVERIFY(std::abs(a - M_PI) < EPS);
}

void TestVector::angle2D_zeroVector_throws() {
    QVERIFY_EXCEPTION_THROWN(
        mylib::angle(mylib::Vector2{0.0, 0.0}, mylib::Vector2{1.0, 1.0}),
        std::invalid_argument);
}

// ===== 3D =====
void TestVector::add3D_basic() {
    auto res = mylib::add(mylib::Vector3{1.0, 2.0, 3.0}, mylib::Vector3{4.0, 5.0, 6.0});
    QCOMPARE(res.x, 5.0);
    QCOMPARE(res.y, 7.0);
    QCOMPARE(res.z, 9.0);
}

void TestVector::dot3D_basic() {
    QCOMPARE(mylib::dot(mylib::Vector3{1.0, 2.0, 3.0}, mylib::Vector3{4.0, 5.0, 6.0}), 32.0);
}

void TestVector::cross3D_basisVectors() {
    auto res = mylib::cross(mylib::Vector3{1.0, 0.0, 0.0}, mylib::Vector3{0.0, 1.0, 0.0});
    QCOMPARE(res.x, 0.0);
    QCOMPARE(res.y, 0.0);
    QCOMPARE(res.z, 1.0);
}

void TestVector::cross3D_parallel_zero() {
    auto res = mylib::cross(mylib::Vector3{2.0, 2.0, 2.0}, mylib::Vector3{4.0, 4.0, 4.0});
    QVERIFY(std::abs(res.x) < EPS);
    QVERIFY(std::abs(res.y) < EPS);
    QVERIFY(std::abs(res.z) < EPS);
}

void TestVector::length3D_basic() {
    QCOMPARE(mylib::length(mylib::Vector3{2.0, 3.0, 6.0}), 7.0);
}

void TestVector::normalize3D_unitLength() {
    auto n = mylib::normalize(mylib::Vector3{0.0, 0.0, 5.0});
    QCOMPARE(n.x, 0.0);
    QCOMPARE(n.y, 0.0);
    QCOMPARE(n.z, 1.0);
}

void TestVector::normalize3D_zeroVector_throws() {
    QVERIFY_EXCEPTION_THROWN(
        mylib::normalize(mylib::Vector3{0.0, 0.0, 0.0}),
        std::invalid_argument);
}

void TestVector::angle3D_parallel_zero() {
    double a = mylib::angle(mylib::Vector3{1.0, 1.0, 1.0}, mylib::Vector3{2.0, 2.0, 2.0});
    QVERIFY(std::abs(a) < EPS);
}

// ===== Параметризованный тест =====
void TestVector::dot2D_parameterized_data() {
    QTest::addColumn<double>("ax");
    QTest::addColumn<double>("ay");
    QTest::addColumn<double>("bx");
    QTest::addColumn<double>("by");
    QTest::addColumn<double>("expected");

    QTest::newRow("orthogonal") << 1.0 << 0.0 << 0.0 << 1.0 << 0.0;
    QTest::newRow("parallel")   << 2.0 << 0.0 << 3.0 << 0.0 << 6.0;
    QTest::newRow("mixed")      << 1.0 << 2.0 << 3.0 << 4.0 << 11.0;
    QTest::newRow("negative")   << -1.0 << 2.0 << 3.0 << -4.0 << -11.0;
    QTest::newRow("zero")       << 0.0 << 0.0 << 5.0 << 5.0 << 0.0;
}

void TestVector::dot2D_parameterized() {
    QFETCH(double, ax);
    QFETCH(double, ay);
    QFETCH(double, bx);
    QFETCH(double, by);
    QFETCH(double, expected);

    double res = mylib::dot(mylib::Vector2{ax, ay}, mylib::Vector2{bx, by});
    QVERIFY(std::abs(res - expected) < EPS);
}

QTEST_MAIN(TestVector)
#include "test_file.moc"