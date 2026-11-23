#include "file.h"
#include <QtTest/QtTest>
#include <cmath>
#include <stdexcept>

class TestCalculator : public QObject
{
    Q_OBJECT

private slots:
    // Позитивные: базовые операции и приоритеты
    void evaluate_basicAddition();
    void evaluate_precedence();
    void evaluate_parentheses();
    void evaluate_unaryMinus();
    void evaluate_unaryPlus();
    void evaluate_floatingPoint();

    // Негативные: ошибки ввода
    void evaluate_emptyString_throws();
    void evaluate_whitespaceOnly_throws();
    void evaluate_divisionByZero_throws();
    void evaluate_invalidChars_throws();
    void evaluate_unmatchedParenthesesOpen_throws();
    void evaluate_unmatchedParenthesesClose_throws();
    void evaluate_trailingChars_throws();

    // Граничные случаи
    void evaluate_deepNesting();
    void evaluate_largeNumbers();
    void evaluate_verySmallNumbers();

    // Параметризованный тест: валидные выражения
    void evaluate_parameterized_data();
    void evaluate_parameterized();
};

// --- Позитивные ---
void TestCalculator::evaluate_basicAddition() {
    QCOMPARE(mylib::evaluateExpression("2 + 3"), 5.0);
}

void TestCalculator::evaluate_precedence() {
    QCOMPARE(mylib::evaluateExpression("2 + 3 * 4"), 14.0);
    QCOMPARE(mylib::evaluateExpression("10 - 2 * 3"), 4.0);
}

void TestCalculator::evaluate_parentheses() {
    QCOMPARE(mylib::evaluateExpression("(2 + 3) * 4"), 20.0);
    QCOMPARE(mylib::evaluateExpression("((1 + 2) * (3 + 4))"), 21.0);
}

void TestCalculator::evaluate_unaryMinus() {
    QCOMPARE(mylib::evaluateExpression("-5"), -5.0);
    QCOMPARE(mylib::evaluateExpression("3 + -2"), 1.0);
    QCOMPARE(mylib::evaluateExpression("-(-5)"), 5.0);
}

void TestCalculator::evaluate_unaryPlus() {
    QCOMPARE(mylib::evaluateExpression("+5"), 5.0);
    QCOMPARE(mylib::evaluateExpression("3 + +2"), 5.0);
}

void TestCalculator::evaluate_floatingPoint() {
    double res = mylib::evaluateExpression("0.1 + 0.2");
    QVERIFY(std::abs(res - 0.3) < 1e-9);
}

// --- Негативные ---
void TestCalculator::evaluate_emptyString_throws() {
    QVERIFY_EXCEPTION_THROWN(mylib::evaluateExpression(""), std::invalid_argument);
}

void TestCalculator::evaluate_whitespaceOnly_throws() {
    QVERIFY_EXCEPTION_THROWN(mylib::evaluateExpression("   "), std::invalid_argument);
}

void TestCalculator::evaluate_divisionByZero_throws() {
    QVERIFY_EXCEPTION_THROWN(mylib::evaluateExpression("5 / 0"), std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN(mylib::evaluateExpression("5 / (2 - 2)"), std::invalid_argument);
}

void TestCalculator::evaluate_invalidChars_throws() {
    QVERIFY_EXCEPTION_THROWN(mylib::evaluateExpression("2 + a"), std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN(mylib::evaluateExpression("2 * * 3"), std::invalid_argument);
}

void TestCalculator::evaluate_unmatchedParenthesesOpen_throws() {
    QVERIFY_EXCEPTION_THROWN(mylib::evaluateExpression("(2 + 3"), std::invalid_argument);
}

void TestCalculator::evaluate_unmatchedParenthesesClose_throws() {
    QVERIFY_EXCEPTION_THROWN(mylib::evaluateExpression("2 + 3)"), std::invalid_argument);
}

void TestCalculator::evaluate_trailingChars_throws() {
    QVERIFY_EXCEPTION_THROWN(mylib::evaluateExpression("2 + 2 abc"), std::invalid_argument);
}

// --- Граничные случаи ---
void TestCalculator::evaluate_deepNesting() {
    QCOMPARE(mylib::evaluateExpression("((((1))))"), 1.0);
}

void TestCalculator::evaluate_largeNumbers() {
    QCOMPARE(mylib::evaluateExpression("1000000 * 1000000"), 1000000000000.0);
}

void TestCalculator::evaluate_verySmallNumbers() {
    double res = mylib::evaluateExpression("0.0001 * 0.0001");
    QVERIFY(std::abs(res - 0.00000001) < 1e-12);
}

// --- Параметризованный тест ---
void TestCalculator::evaluate_parameterized_data() {
    QTest::addColumn<QString>("expr");
    QTest::addColumn<double>("expected");

    QTest::newRow("simple_sub") << "10 - 5" << 5.0;
    QTest::newRow("mul_div") << "10 / 2 * 3" << 15.0;
    QTest::newRow("complex") << "2 * (3 + 4) - 1" << 13.0;
    QTest::newRow("unary_chain") << "---5" << -5.0;
    QTest::newRow("decimal") << "2.5 * 2" << 5.0;
}

void TestCalculator::evaluate_parameterized() {
    QFETCH(QString, expr);
    QFETCH(double, expected);

    double result = mylib::evaluateExpression(expr.toStdString());
    QVERIFY(std::abs(result - expected) < 1e-9);
}

QTEST_MAIN(TestCalculator)
#include "test_file.moc"