#include "file.h"
#include <QtTest/QtTest>
#include <cmath>
#include <algorithm>
#include <array>

class TestQuadratic : public QObject
{
    Q_OBJECT

private slots:
    // Квадратные уравнения (a != 0)
    void solveQuadratic_twoDistinctRoots();
    void solveQuadratic_oneRoot_Dzero();
    void solveQuadratic_noRealRoots_Dnegative();
    void solveQuadratic_cIsZero_oneRootIsZero();
    void solveQuadratic_negativeA();

    // Вырожденные случаи (a == 0)
    void solveQuadratic_degenerate_linear_oneRoot();
    void solveQuadratic_degenerate_constant_noRoots();
    void solveQuadratic_degenerate_allZeros_infinite();

    // Параметризованные тесты: квадратные уравнения
    void solveQuadratic_paramQuad_data();
    void solveQuadratic_paramQuad();

    // Параметризованные тесты: линейные уравнения
    void solveQuadratic_paramLin_data();
    void solveQuadratic_paramLin();

    // Граничные случаи и точность
    void solveQuadratic_largeCoefficients();
    void solveQuadratic_smallCoefficients();
    void solveQuadratic_rootsSorting();
};

// --- Квадратные уравнения ---
void TestQuadratic::solveQuadratic_twoDistinctRoots() {
    double x1 = 0, x2 = 0;
    mylib::RootCount count = mylib::solveQuadratic(1, -3, 2, x1, x2); // x^2 - 3x + 2 = 0
    QCOMPARE(count, mylib::RootCount::Two);

    std::array<double, 2> roots = {x1, x2};
    std::sort(roots.begin(), roots.end());
    QVERIFY(std::abs(roots[0] - 1.0) < 1e-9);
    QVERIFY(std::abs(roots[1] - 2.0) < 1e-9);
}

void TestQuadratic::solveQuadratic_oneRoot_Dzero() {
    double x1 = 0, x2 = 0;
    mylib::RootCount count = mylib::solveQuadratic(1, -2, 1, x1, x2); // (x-1)^2 = 0
    QCOMPARE(count, mylib::RootCount::One);
    QVERIFY(std::abs(x1 - 1.0) < 1e-9);
}

void TestQuadratic::solveQuadratic_noRealRoots_Dnegative() {
    double x1 = 0, x2 = 0;
    mylib::RootCount count = mylib::solveQuadratic(1, 0, 1, x1, x2); // x^2 + 1 = 0
    QCOMPARE(count, mylib::RootCount::None);
}

void TestQuadratic::solveQuadratic_cIsZero_oneRootIsZero() {
    double x1 = 0, x2 = 0;
    mylib::RootCount count = mylib::solveQuadratic(1, -5, 0, x1, x2); // x^2 - 5x = 0
    QCOMPARE(count, mylib::RootCount::Two);

    std::array<double, 2> roots = {x1, x2};
    std::sort(roots.begin(), roots.end());
    QVERIFY(std::abs(roots[0] - 0.0) < 1e-9);
    QVERIFY(std::abs(roots[1] - 5.0) < 1e-9);
}

void TestQuadratic::solveQuadratic_negativeA() {
    double x1 = 0, x2 = 0;
    mylib::RootCount count = mylib::solveQuadratic(-1, 0, 4, x1, x2); // -x^2 + 4 = 0
    QCOMPARE(count, mylib::RootCount::Two);

    std::array<double, 2> roots = {x1, x2};
    std::sort(roots.begin(), roots.end());
    QVERIFY(std::abs(roots[0] - (-2.0)) < 1e-9);
    QVERIFY(std::abs(roots[1] - 2.0) < 1e-9);
}

// --- Вырожденные случаи ---
void TestQuadratic::solveQuadratic_degenerate_linear_oneRoot() {
    double x1 = 0, x2 = 0;
    mylib::RootCount count = mylib::solveQuadratic(0, 2, -6, x1, x2); // 2x - 6 = 0
    QCOMPARE(count, mylib::RootCount::One);
    QVERIFY(std::abs(x1 - 3.0) < 1e-9);
}

void TestQuadratic::solveQuadratic_degenerate_constant_noRoots() {
    double x1 = 0, x2 = 0;
    mylib::RootCount count = mylib::solveQuadratic(0, 0, 5, x1, x2); // 5 = 0
    QCOMPARE(count, mylib::RootCount::None);
}

void TestQuadratic::solveQuadratic_degenerate_allZeros_infinite() {
    double x1 = 0, x2 = 0;
    mylib::RootCount count = mylib::solveQuadratic(0, 0, 0, x1, x2); // 0 = 0
    QCOMPARE(count, mylib::RootCount::Infinite);
}

// --- Параметризованные тесты: квадратные ---
void TestQuadratic::solveQuadratic_paramQuad_data() {
    QTest::addColumn<double>("a");
    QTest::addColumn<double>("b");
    QTest::addColumn<double>("c");
    QTest::addColumn<mylib::RootCount>("expectedCount");

    QTest::newRow("x^2-4=0") << 1.0 << 0.0 << -4.0 << mylib::RootCount::Two;
    QTest::newRow("2x^2+8x+8=0") << 2.0 << 8.0 << 8.0 << mylib::RootCount::One;
    QTest::newRow("x^2+x+1=0") << 1.0 << 1.0 << 1.0 << mylib::RootCount::None;
}

void TestQuadratic::solveQuadratic_paramQuad() {
    QFETCH(double, a);
    QFETCH(double, b);
    QFETCH(double, c);
    QFETCH(mylib::RootCount, expectedCount);

    double x1 = 0, x2 = 0;
    QCOMPARE(mylib::solveQuadratic(a, b, c, x1, x2), expectedCount);
}

// --- Параметризованные тесты: линейные ---
void TestQuadratic::solveQuadratic_paramLin_data() {
    QTest::addColumn<double>("b");
    QTest::addColumn<double>("c");
    QTest::addColumn<mylib::RootCount>("expectedCount");

    QTest::newRow("3x-9=0") << 3.0 << -9.0 << mylib::RootCount::One;
    QTest::newRow("0x+5=0") << 0.0 << 5.0 << mylib::RootCount::None;
    QTest::newRow("0x+0=0") << 0.0 << 0.0 << mylib::RootCount::Infinite;
}

void TestQuadratic::solveQuadratic_paramLin() {
    QFETCH(double, b);
    QFETCH(double, c);
    QFETCH(mylib::RootCount, expectedCount);

    double x1 = 0, x2 = 0;
    QCOMPARE(mylib::solveQuadratic(0.0, b, c, x1, x2), expectedCount);
}

// --- Граничные случаи ---
void TestQuadratic::solveQuadratic_largeCoefficients() {
    double x1 = 0, x2 = 0;
    // x^2 - 2000000x + 1000000 = 0
    mylib::RootCount count = mylib::solveQuadratic(1, -2000000, 1000000, x1, x2);
    QCOMPARE(count, mylib::RootCount::Two);
    QVERIFY(x1 != 0 || x2 != 0); // Просто проверяем, что не упало и корни есть
}

void TestQuadratic::solveQuadratic_smallCoefficients() {
    double x1 = 0, x2 = 0;
    // 0.0001x^2 + 0.0002x + 0.0001 = 0 -> D=0, x=-1
    mylib::RootCount count = mylib::solveQuadratic(0.0001, 0.0002, 0.0001, x1, x2);
    QCOMPARE(count, mylib::RootCount::One);
    QVERIFY(std::abs(x1 - (-1.0)) < 1e-5);
}

void TestQuadratic::solveQuadratic_rootsSorting() {
    double x1 = 0, x2 = 0;
    // a < 0 меняет порядок корней в формуле, но сортировка в тесте это исправит
    mylib::solveQuadratic(-1, 0, 9, x1, x2);
    std::array<double, 2> roots = {x1, x2};
    std::sort(roots.begin(), roots.end());
    QVERIFY(std::abs(roots[0] - (-3.0)) < 1e-9);
    QVERIFY(std::abs(roots[1] - 3.0) < 1e-9);
}

QTEST_MAIN(TestQuadratic)
#include "test_file.moc"