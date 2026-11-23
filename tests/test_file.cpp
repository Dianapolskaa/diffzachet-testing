#include "file.h"
#include <QtTest/QtTest>
#include <cmath>
#include <stdexcept>

class TestShoppingCart : public QObject
{
    Q_OBJECT

private slots:
    // calculateTotal
    void calculateTotal_emptyCart_zero();
    void calculateTotal_singleItem();
    void calculateTotal_multipleItems();
    void calculateTotal_zeroPrice_zero();
    void calculateTotal_zeroQuantity_zero();
    void calculateTotal_roundingCents();
    void calculateTotal_negativePrice_throws();
    void calculateTotal_negativeQuantity_throws();

    // applyDiscount
    void applyDiscount_belowThreshold_noDiscount();
    void applyDiscount_exactlyThreshold_applied();
    void applyDiscount_aboveThreshold_applied();
    void applyDiscount_zeroPercent_noChange();
    void applyDiscount_invalidPercent_throws();

    // calculateWithVAT
    void calculateWithVAT_zeroRate_noChange();
    void calculateWithVAT_standard20();
    void calculateWithVAT_negativeRate_throws();

    // applyBuy3Pay2
    void applyBuy3Pay2_lessThan3_noDiscount();
    void applyBuy3Pay2_exactly3_paysFor2();
    void applyBuy3Pay2_six_paysFor4();
    void applyBuy3Pay2_multipleItems();

    // calculateFinal (сквозной)
    void calculateFinal_complexScenario();

    // Параметризованный тест
    void calculateTotal_parameterized_data();
    void calculateTotal_parameterized();
};

// --- calculateTotal ---
void TestShoppingCart::calculateTotal_emptyCart_zero() {
    QCOMPARE(mylib::calculateTotal({}), 0.0);
}

void TestShoppingCart::calculateTotal_singleItem() {
    QCOMPARE(mylib::calculateTotal({{"Apple", 10.0, 3}}), 30.0);
}

void TestShoppingCart::calculateTotal_multipleItems() {
    std::vector<mylib::CartItem> cart = {
        {"Apple", 10.0, 3},
        {"Banana", 5.5, 2}
    };
    QCOMPARE(mylib::calculateTotal(cart), 41.0);
}

void TestShoppingCart::calculateTotal_zeroPrice_zero() {
    QCOMPARE(mylib::calculateTotal({{"Free", 0.0, 5}}), 0.0);
}

void TestShoppingCart::calculateTotal_zeroQuantity_zero() {
    QCOMPARE(mylib::calculateTotal({{"Item", 100.0, 0}}), 0.0);
}

void TestShoppingCart::calculateTotal_roundingCents() {
    // 3 * 3.333 = 9.999 -> округление до 10.00
    QCOMPARE(mylib::calculateTotal({{"Item", 3.333, 3}}), 10.0);
}

void TestShoppingCart::calculateTotal_negativePrice_throws() {
    QVERIFY_EXCEPTION_THROWN(
        mylib::calculateTotal({{"Bad", -1.0, 1}}),
        std::invalid_argument
        );
}

void TestShoppingCart::calculateTotal_negativeQuantity_throws() {
    QVERIFY_EXCEPTION_THROWN(
        mylib::calculateTotal({{"Bad", 10.0, -1}}),
        std::invalid_argument
        );
}

// --- applyDiscount ---
void TestShoppingCart::applyDiscount_belowThreshold_noDiscount() {
    QCOMPARE(mylib::applyDiscount(99.0, 100.0, 10.0), 99.0);
}

void TestShoppingCart::applyDiscount_exactlyThreshold_applied() {
    // 100 * 0.9 = 90
    QCOMPARE(mylib::applyDiscount(100.0, 100.0, 10.0), 90.0);
}

void TestShoppingCart::applyDiscount_aboveThreshold_applied() {
    // 200 * 0.9 = 180
    QCOMPARE(mylib::applyDiscount(200.0, 100.0, 10.0), 180.0);
}

void TestShoppingCart::applyDiscount_zeroPercent_noChange() {
    QCOMPARE(mylib::applyDiscount(150.0, 100.0, 0.0), 150.0);
}

void TestShoppingCart::applyDiscount_invalidPercent_throws() {
    QVERIFY_EXCEPTION_THROWN(
        mylib::applyDiscount(100.0, 50.0, 150.0),
        std::invalid_argument
        );
}

// --- calculateWithVAT ---
void TestShoppingCart::calculateWithVAT_zeroRate_noChange() {
    QCOMPARE(mylib::calculateWithVAT(100.0, 0.0), 100.0);
}

void TestShoppingCart::calculateWithVAT_standard20() {
    // 100 * 1.2 = 120
    QCOMPARE(mylib::calculateWithVAT(100.0, 20.0), 120.0);
}

void TestShoppingCart::calculateWithVAT_negativeRate_throws() {
    QVERIFY_EXCEPTION_THROWN(
        mylib::calculateWithVAT(100.0, -5.0),
        std::invalid_argument
        );
}

// --- applyBuy3Pay2 ---
void TestShoppingCart::applyBuy3Pay2_lessThan3_noDiscount() {
    QCOMPARE(mylib::applyBuy3Pay2({{"Item", 10.0, 2}}), 20.0);
}

void TestShoppingCart::applyBuy3Pay2_exactly3_paysFor2() {
    // 3 штуки по 10 -> платим за 2 = 20
    QCOMPARE(mylib::applyBuy3Pay2({{"Item", 10.0, 3}}), 20.0);
}

void TestShoppingCart::applyBuy3Pay2_six_paysFor4() {
    // 6 штук по 10 -> 6 - 6/3 = 4 оплачиваемых = 40
    QCOMPARE(mylib::applyBuy3Pay2({{"Item", 10.0, 6}}), 40.0);
}

void TestShoppingCart::applyBuy3Pay2_multipleItems() {
    std::vector<mylib::CartItem> cart = {
        {"A", 10.0, 3}, // 2 оплачиваемых = 20
        {"B", 5.0, 4}   // 4 - 4/3 = 3 оплачиваемых = 15
    };
    QCOMPARE(mylib::applyBuy3Pay2(cart), 35.0);
}

// --- calculateFinal (сквозной) ---
void TestShoppingCart::calculateFinal_complexScenario() {
    // Корзина: 6 яблок по 100 руб.
    // 1. Акция "3 по цене 2": 6 - 6/3 = 4 оплачиваемых = 400 руб.
    // 2. Скидка 10% при пороге 300: 400 >= 300, значит 400 * 0.9 = 360 руб.
    // 3. НДС 20%: 360 * 1.2 = 432 руб.
    std::vector<mylib::CartItem> cart = {{"Apple", 100.0, 6}};
    QCOMPARE(mylib::calculateFinal(cart, 300.0, 10.0, 20.0), 432.0);
}

// --- Параметризованный тест ---
void TestShoppingCart::calculateTotal_parameterized_data() {
    QTest::addColumn<double>("price");
    QTest::addColumn<int>("quantity");
    QTest::addColumn<double>("expected");

    QTest::newRow("zero_price") << 0.0 << 5 << 0.0;
    QTest::newRow("zero_qty") << 100.0 << 0 << 0.0;
    QTest::newRow("normal") << 15.5 << 4 << 62.0;
    QTest::newRow("rounding_up") << 3.333 << 3 << 10.0;
    QTest::newRow("rounding_down") << 3.331 << 3 << 9.99;
}

void TestShoppingCart::calculateTotal_parameterized() {
    QFETCH(double, price);
    QFETCH(int, quantity);
    QFETCH(double, expected);

    std::vector<mylib::CartItem> cart = {{"Item", price, quantity}};
    QCOMPARE(mylib::calculateTotal(cart), expected);
}

QTEST_MAIN(TestShoppingCart)
#include "test_file.moc"