#include "file.h"
#include <QtTest/QtTest>
#include <cmath>
#include <stdexcept>

class TestSalary : public QObject
{
    Q_OBJECT

private slots:
    // Налог (позитивные и граничные)
    void calculateProgressiveTax_zero_zero();
    void calculateProgressiveTax_belowFirstBracket();
    void calculateProgressiveTax_exactlyFirstBracketBoundary();
    void calculateProgressiveTax_inSecondBracket();
    void calculateProgressiveTax_exactlySecondBracketBoundary();
    void calculateProgressiveTax_aboveSecondBracket();

    // Налог (негативные)
    void calculateProgressiveTax_negative_throws();

    // KPI (позитивные и граничные)
    void calculateKpiBonus_belowThreshold_zero();
    void calculateKpiBonus_exactlyFirstThreshold();
    void calculateKpiBonus_exactlySecondThreshold();
    void calculateKpiBonus_highKpi();

    // KPI (негативные)
    void calculateKpiBonus_negativeKpi_throws();
    void calculateKpiBonus_negativeSalary_throws();

    // Итоговая зарплата
    void calculateNetSalary_zeroBaseAndKpi();
    void calculateNetSalary_highKpi_highSalary();

    // Параметризованный тест на границы налоговых ступеней
    void calculateProgressiveTax_parameterized_data();
    void calculateProgressiveTax_parameterized();
};

// --- Налог ---
void TestSalary::calculateProgressiveTax_zero_zero() {
    QCOMPARE(mylib::calculateProgressiveTax(0.0), 0.0);
}

void TestSalary::calculateProgressiveTax_belowFirstBracket() {
    QCOMPARE(mylib::calculateProgressiveTax(10000.0), 1300.0);
}

void TestSalary::calculateProgressiveTax_exactlyFirstBracketBoundary() {
    // Ровно 50 000 -> 13%
    QCOMPARE(mylib::calculateProgressiveTax(50000.0), 6500.0);
}

void TestSalary::calculateProgressiveTax_inSecondBracket() {
    // 75 000 -> 50000*0.13 + 25000*0.15 = 6500 + 3750 = 10250
    QCOMPARE(mylib::calculateProgressiveTax(75000.0), 10250.0);
}

void TestSalary::calculateProgressiveTax_exactlySecondBracketBoundary() {
    // Ровно 100 000 -> 6500 + 50000*0.15 = 14000
    QCOMPARE(mylib::calculateProgressiveTax(100000.0), 14000.0);
}

void TestSalary::calculateProgressiveTax_aboveSecondBracket() {
    // 150 000 -> 14000 + 50000*0.20 = 24000
    QCOMPARE(mylib::calculateProgressiveTax(150000.0), 24000.0);
}

void TestSalary::calculateProgressiveTax_negative_throws() {
    QVERIFY_EXCEPTION_THROWN(mylib::calculateProgressiveTax(-100.0), std::invalid_argument);
}

// --- KPI ---
void TestSalary::calculateKpiBonus_belowThreshold_zero() {
    QCOMPARE(mylib::calculateKpiBonus(100000.0, 49.0), 0.0);
}

void TestSalary::calculateKpiBonus_exactlyFirstThreshold() {
    // KPI = 50 -> 10%
    QCOMPARE(mylib::calculateKpiBonus(100000.0, 50.0), 10000.0);
}

void TestSalary::calculateKpiBonus_exactlySecondThreshold() {
    // KPI = 80 -> 20%
    QCOMPARE(mylib::calculateKpiBonus(100000.0, 80.0), 20000.0);
}

void TestSalary::calculateKpiBonus_highKpi() {
    QCOMPARE(mylib::calculateKpiBonus(50000.0, 120.0), 10000.0);
}

void TestSalary::calculateKpiBonus_negativeKpi_throws() {
    QVERIFY_EXCEPTION_THROWN(mylib::calculateKpiBonus(100000.0, -5.0), std::invalid_argument);
}

void TestSalary::calculateKpiBonus_negativeSalary_throws() {
    QVERIFY_EXCEPTION_THROWN(mylib::calculateKpiBonus(-10000.0, 50.0), std::invalid_argument);
}

// --- Итоговая зарплата ---
void TestSalary::calculateNetSalary_zeroBaseAndKpi() {
    QCOMPARE(mylib::calculateNetSalary(0.0, 0.0), 0.0);
}

void TestSalary::calculateNetSalary_highKpi_highSalary() {
    // Оклад 80 000, KPI 80 (бонус 20% = 16 000). Gross = 96 000.
    // Налог: 50000*0.13 + 46000*0.15 = 6500 + 6900 = 13400.
    // Net = 96000 - 13400 = 82600.
    QCOMPARE(mylib::calculateNetSalary(80000.0, 80.0), 82600.0);
}

// --- Параметризованный тест ---
void TestSalary::calculateProgressiveTax_parameterized_data() {
    QTest::addColumn<double>("gross");
    QTest::addColumn<double>("expectedTax");

    QTest::newRow("zero") << 0.0 << 0.0;
    QTest::newRow("bracket1_max") << 50000.0 << 6500.0;
    QTest::newRow("bracket2_mid") << 75000.0 << 10250.0;
    QTest::newRow("bracket2_max") << 100000.0 << 14000.0;
    QTest::newRow("bracket3_mid") << 150000.0 << 24000.0;
}

void TestSalary::calculateProgressiveTax_parameterized() {
    QFETCH(double, gross);
    QFETCH(double, expectedTax);

    double result = mylib::calculateProgressiveTax(gross);
    QVERIFY(std::abs(result - expectedTax) < 1e-9);
}

QTEST_MAIN(TestSalary)
#include "test_file.moc"