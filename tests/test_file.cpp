#include "file.h"
#include <QtTest/QtTest>
#include <cmath>
#include <stdexcept>

static const double EPS = 1e-9;

class TestMatrix : public QObject
{
    Q_OBJECT

private slots:
    // createMatrix
    void createMatrix_valid();
    void createMatrix_invalidDimensions_throws();

    // identityMatrix
    void identityMatrix_2x2();
    void identityMatrix_1x1();
    void identityMatrix_invalid_throws();

    // add
    void add_basic();
    void add_zeroMatrix();
    void add_incompatibleDimensions_throws();

    // multiply
    void multiply_basic();
    void multiply_identityMatrix();
    void multiply_incompatibleDimensions_throws();

    // transpose
    void transpose_square();
    void transpose_rectangular();
    void transpose_1x1();

    // determinant
    void determinant_1x1();
    void determinant_2x2();
    void determinant_3x3();
    void determinant_singular_zero();
    void determinant_identity_one();
    void determinant_nonSquare_throws();

    // Параметризованные тесты
    void add_parameterized_data();
    void add_parameterized();
    void determinant_parameterized_data();
    void determinant_parameterized();
};

// --- createMatrix ---
void TestMatrix::createMatrix_valid() {
    auto m = mylib::createMatrix(3, 4);
    QCOMPARE(mylib::rows(m), 3);
    QCOMPARE(mylib::cols(m), 4);
    QCOMPARE(m[0][0], 0.0);
}

void TestMatrix::createMatrix_invalidDimensions_throws() {
    QVERIFY_EXCEPTION_THROWN(mylib::createMatrix(0, 5), std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN(mylib::createMatrix(3, -1), std::invalid_argument);
}

// --- identityMatrix ---
void TestMatrix::identityMatrix_2x2() {
    auto m = mylib::identityMatrix(2);
    QCOMPARE(m[0][0], 1.0);
    QCOMPARE(m[0][1], 0.0);
    QCOMPARE(m[1][0], 0.0);
    QCOMPARE(m[1][1], 1.0);
}

void TestMatrix::identityMatrix_1x1() {
    auto m = mylib::identityMatrix(1);
    QCOMPARE(m[0][0], 1.0);
}

void TestMatrix::identityMatrix_invalid_throws() {
    QVERIFY_EXCEPTION_THROWN(mylib::identityMatrix(0), std::invalid_argument);
}

// --- add ---
void TestMatrix::add_basic() {
    auto a = mylib::createMatrix(2, 2);
    auto b = mylib::createMatrix(2, 2);
    a[0][0] = 1.0; a[0][1] = 2.0;
    a[1][0] = 3.0; a[1][1] = 4.0;
    b[0][0] = 5.0; b[0][1] = 6.0;
    b[1][0] = 7.0; b[1][1] = 8.0;

    auto res = mylib::add(a, b);
    QCOMPARE(res[0][0], 6.0);
    QCOMPARE(res[0][1], 8.0);
    QCOMPARE(res[1][0], 10.0);
    QCOMPARE(res[1][1], 12.0);
}

void TestMatrix::add_zeroMatrix() {
    auto a = mylib::createMatrix(2, 2);
    a[0][0] = 5.0;
    auto zero = mylib::createMatrix(2, 2);
    auto res = mylib::add(a, zero);
    QCOMPARE(res[0][0], 5.0);
}

void TestMatrix::add_incompatibleDimensions_throws() {
    auto a = mylib::createMatrix(2, 3);
    auto b = mylib::createMatrix(3, 2);
    QVERIFY_EXCEPTION_THROWN(mylib::add(a, b), std::invalid_argument);
}

// --- multiply ---
void TestMatrix::multiply_basic() {
    auto a = mylib::createMatrix(2, 2);
    auto b = mylib::createMatrix(2, 2);
    a[0][0] = 1.0; a[0][1] = 2.0;
    a[1][0] = 3.0; a[1][1] = 4.0;
    b[0][0] = 5.0; b[0][1] = 6.0;
    b[1][0] = 7.0; b[1][1] = 8.0;

    auto res = mylib::multiply(a, b);
    QCOMPARE(res[0][0], 19.0);
    QCOMPARE(res[0][1], 22.0);
    QCOMPARE(res[1][0], 43.0);
    QCOMPARE(res[1][1], 50.0);
}

void TestMatrix::multiply_identityMatrix() {
    auto a = mylib::createMatrix(2, 2);
    a[0][0] = 1.0; a[0][1] = 2.0;
    a[1][0] = 3.0; a[1][1] = 4.0;
    auto id = mylib::identityMatrix(2);

    auto res = mylib::multiply(a, id);
    QCOMPARE(res[0][0], 1.0);
    QCOMPARE(res[0][1], 2.0);
    QCOMPARE(res[1][0], 3.0);
    QCOMPARE(res[1][1], 4.0);
}

void TestMatrix::multiply_incompatibleDimensions_throws() {
    auto a = mylib::createMatrix(2, 3);
    auto b = mylib::createMatrix(2, 2);
    QVERIFY_EXCEPTION_THROWN(mylib::multiply(a, b), std::invalid_argument);
}

// --- transpose ---
void TestMatrix::transpose_square() {
    auto m = mylib::createMatrix(2, 2);
    m[0][0] = 1.0; m[0][1] = 2.0;
    m[1][0] = 3.0; m[1][1] = 4.0;

    auto t = mylib::transpose(m);
    QCOMPARE(t[0][0], 1.0);
    QCOMPARE(t[0][1], 3.0);
    QCOMPARE(t[1][0], 2.0);
    QCOMPARE(t[1][1], 4.0);
}

void TestMatrix::transpose_rectangular() {
    auto m = mylib::createMatrix(2, 3);
    m[0][0] = 1.0; m[0][1] = 2.0; m[0][2] = 3.0;
    m[1][0] = 4.0; m[1][1] = 5.0; m[1][2] = 6.0;

    auto t = mylib::transpose(m);
    QCOMPARE(mylib::rows(t), 3);
    QCOMPARE(mylib::cols(t), 2);
    QCOMPARE(t[0][0], 1.0);
    QCOMPARE(t[0][1], 4.0);
    QCOMPARE(t[2][1], 6.0);
}

void TestMatrix::transpose_1x1() {
    auto m = mylib::createMatrix(1, 1);
    m[0][0] = 5.0;
    auto t = mylib::transpose(m);
    QCOMPARE(t[0][0], 5.0);
}

// --- determinant ---
void TestMatrix::determinant_1x1() {
    auto m = mylib::createMatrix(1, 1);
    m[0][0] = 7.0;
    QCOMPARE(mylib::determinant(m), 7.0);
}

void TestMatrix::determinant_2x2() {
    auto m = mylib::createMatrix(2, 2);
    m[0][0] = 1.0; m[0][1] = 2.0;
    m[1][0] = 3.0; m[1][1] = 4.0;
    QCOMPARE(mylib::determinant(m), -2.0);
}

void TestMatrix::determinant_3x3() {
    auto m = mylib::createMatrix(3, 3);
    m[0][0] = 1.0; m[0][1] = 2.0; m[0][2] = 3.0;
    m[1][0] = 4.0; m[1][1] = 5.0; m[1][2] = 6.0;
    m[2][0] = 7.0; m[2][1] = 8.0; m[2][2] = 9.0;
    QCOMPARE(mylib::determinant(m), 0.0); // Вырожденная матрица
}

void TestMatrix::determinant_singular_zero() {
    auto m = mylib::createMatrix(2, 2);
    m[0][0] = 1.0; m[0][1] = 2.0;
    m[1][0] = 2.0; m[1][1] = 4.0; // Вторая строка = 2 * первая
    QCOMPARE(mylib::determinant(m), 0.0);
}

void TestMatrix::determinant_identity_one() {
    auto m = mylib::identityMatrix(3);
    QCOMPARE(mylib::determinant(m), 1.0);
}

void TestMatrix::determinant_nonSquare_throws() {
    auto m = mylib::createMatrix(2, 3);
    QVERIFY_EXCEPTION_THROWN(mylib::determinant(m), std::invalid_argument);
}

// --- Параметризованные тесты ---
void TestMatrix::add_parameterized_data() {
    QTest::addColumn<double>("a00");
    QTest::addColumn<double>("b00");
    QTest::addColumn<double>("expected");

    QTest::newRow("positive") << 1.0 << 2.0 << 3.0;
    QTest::newRow("negative") << -1.0 << -2.0 << -3.0;
    QTest::newRow("zero") << 0.0 << 5.0 << 5.0;
    QTest::newRow("mixed") << 3.0 << -3.0 << 0.0;
}

void TestMatrix::add_parameterized() {
    QFETCH(double, a00);
    QFETCH(double, b00);
    QFETCH(double, expected);

    auto a = mylib::createMatrix(1, 1);
    auto b = mylib::createMatrix(1, 1);
    a[0][0] = a00;
    b[0][0] = b00;

    auto res = mylib::add(a, b);
    QCOMPARE(res[0][0], expected);
}

void TestMatrix::determinant_parameterized_data() {
    QTest::addColumn<std::vector<std::vector<double>>>("matrix");
    QTest::addColumn<double>("expected");

    QTest::newRow("identity_2x2")
        << std::vector<std::vector<double>>{{1.0, 0.0}, {0.0, 1.0}}
        << 1.0;

    QTest::newRow("diagonal_2x2")
        << std::vector<std::vector<double>>{{2.0, 0.0}, {0.0, 3.0}}
        << 6.0;

    QTest::newRow("singular_2x2")
        << std::vector<std::vector<double>>{{1.0, 2.0}, {2.0, 4.0}}
        << 0.0;
}

void TestMatrix::determinant_parameterized() {
    QFETCH(std::vector<std::vector<double>>, matrix);
    QFETCH(double, expected);

    double det = mylib::determinant(matrix);
    QVERIFY(std::abs(det - expected) < EPS);
}

QTEST_MAIN(TestMatrix)
#include "test_file.moc"