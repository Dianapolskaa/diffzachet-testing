#include "file.h"
#include <QtTest/QtTest>
#include <stdexcept>

class TestGcdLcm : public QObject
{
    Q_OBJECT

private slots:
    // --- НОД (GCD) ---
    void gcd_positiveNumbers();
    void gcd_oneIsZero();
    void gcd_bothZero();
    void gcd_negativeNumbers();
    void gcd_coprimeNumbers();
    void gcd_equalNumbers();

    // --- НОК (LCM) ---
    void lcm_positiveNumbers();
    void lcm_oneIsZero();
    void lcm_negativeNumbers();
    void lcm_overflow_throws();

    // --- Разложение на множители ---
    void primeFactors_basic();
    void primeFactors_primeNumber();
    void primeFactors_oneOrLess();
    void primeFactors_negativeNumber();

    // --- Параметризованные тесты ---
    void gcd_parameterized_data();
    void gcd_parameterized();
    void lcm_parameterized_data();
    void lcm_parameterized();
};

// --- НОД ---
void TestGcdLcm::gcd_positiveNumbers() {
    QCOMPARE(mylib::gcd(12, 8), 4LL);
}

void TestGcdLcm::gcd_oneIsZero() {
    QCOMPARE(mylib::gcd(5, 0), 5LL);
    QCOMPARE(mylib::gcd(0, 7), 7LL);
}

void TestGcdLcm::gcd_bothZero() {
    QCOMPARE(mylib::gcd(0, 0), 0LL);
}

void TestGcdLcm::gcd_negativeNumbers() {
    QCOMPARE(mylib::gcd(-12, 8), 4LL);
    QCOMPARE(mylib::gcd(-12, -8), 4LL);
}

void TestGcdLcm::gcd_coprimeNumbers() {
    QCOMPARE(mylib::gcd(7, 9), 1LL);
}

void TestGcdLcm::gcd_equalNumbers() {
    QCOMPARE(mylib::gcd(15, 15), 15LL);
}

// --- НОК ---
void TestGcdLcm::lcm_positiveNumbers() {
    QCOMPARE(mylib::lcm(4, 6), 12LL);
}

void TestGcdLcm::lcm_oneIsZero() {
    QCOMPARE(mylib::lcm(5, 0), 0LL);
    QCOMPARE(mylib::lcm(0, 7), 0LL);
}

void TestGcdLcm::lcm_negativeNumbers() {
    QCOMPARE(mylib::lcm(-4, 6), 12LL);
}

void TestGcdLcm::lcm_overflow_throws() {
    // Два больших взаимно простых числа, чьё произведение > LLONG_MAX (~9.22e18).
    // 3037000493 и 3037000507 — оба простые, gcd = 1, lcm = произведение ≈ 9.22e18 + переполнение.
    QVERIFY_EXCEPTION_THROWN(
        mylib::lcm(3037000493LL, 3037000507LL),
        std::overflow_error
        );
}

// --- Разложение на множители ---
void TestGcdLcm::primeFactors_basic() {
    auto factors = mylib::primeFactors(12);
    QCOMPARE(factors.size(), 3u);
    QCOMPARE(factors[0], 2LL);
    QCOMPARE(factors[1], 2LL);
    QCOMPARE(factors[2], 3LL);
}

void TestGcdLcm::primeFactors_primeNumber() {
    auto factors = mylib::primeFactors(13);
    QCOMPARE(factors.size(), 1u);
    QCOMPARE(factors[0], 13LL);
}

void TestGcdLcm::primeFactors_oneOrLess() {
    // Пустой вектор только для -1, 0, 1 (после взятия модуля остаётся <= 1)
    QVERIFY(mylib::primeFactors(1).empty());
    QVERIFY(mylib::primeFactors(0).empty());
    QVERIFY(mylib::primeFactors(-1).empty());
}

void TestGcdLcm::primeFactors_negativeNumber() {
    // Для отрицательных берём модуль: -10 -> {2, 5}
    auto factors = mylib::primeFactors(-10);
    QCOMPARE(factors.size(), 2u);
    QCOMPARE(factors[0], 2LL);
    QCOMPARE(factors[1], 5LL);

    // -5 -> {5} (не пустой!)
    auto factors5 = mylib::primeFactors(-5);
    QCOMPARE(factors5.size(), 1u);
    QCOMPARE(factors5[0], 5LL);
}

// --- Параметризованные тесты ---
void TestGcdLcm::gcd_parameterized_data() {
    QTest::addColumn<long long>("a");
    QTest::addColumn<long long>("b");
    QTest::addColumn<long long>("expected");

    QTest::newRow("large_primes") << 1000000007LL << 1000000009LL << 1LL;
    QTest::newRow("one_and_n") << 1LL << 100LL << 1LL;
    QTest::newRow("multiple") << 100LL << 25LL << 25LL;
}

void TestGcdLcm::gcd_parameterized() {
    QFETCH(long long, a);
    QFETCH(long long, b);
    QFETCH(long long, expected);
    QCOMPARE(mylib::gcd(a, b), expected);
}

void TestGcdLcm::lcm_parameterized_data() {
    QTest::addColumn<long long>("a");
    QTest::addColumn<long long>("b");
    QTest::addColumn<long long>("expected");

    QTest::newRow("coprime") << 3LL << 7LL << 21LL;
    QTest::newRow("multiple") << 4LL << 8LL << 8LL;
    QTest::newRow("large") << 1000000LL << 1000000LL << 1000000LL;
}

void TestGcdLcm::lcm_parameterized() {
    QFETCH(long long, a);
    QFETCH(long long, b);
    QFETCH(long long, expected);
    QCOMPARE(mylib::lcm(a, b), expected);
}

QTEST_MAIN(TestGcdLcm)
#include "test_file.moc"