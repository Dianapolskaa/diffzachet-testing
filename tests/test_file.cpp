#include "file.h"
#include <QtTest/QtTest>
#include <stdexcept>

class TestBankAccount : public QObject
{
    Q_OBJECT

private slots:
    // Конструктор и геттеры
    void constructor_default();
    void constructor_withValues();
    void constructor_negativeBalance_throws();

    // Пополнение
    void deposit_positive();
    void deposit_zero_throws();
    void deposit_negative_throws();

    // Снятие
    void withdraw_positive();
    void withdraw_exactBalance_toZero();
    void withdraw_moreThanBalance_throws();
    void withdraw_negative_throws();

    // Проценты
    void applyInterest_basic();
    void applyInterest_zeroBalance_noInterest();
    void applyInterest_zeroRate_noInterest();
    void applyInterest_negativePeriods_throws();

    // Проверка средств
    void hasSufficientFunds_true();
    void hasSufficientFunds_false();

    // История
    void history_tracksOperations();

    // Параметризованный тест
    void deposit_parameterized_data();
    void deposit_parameterized();
};

// --- Конструктор ---
void TestBankAccount::constructor_default() {
    mylib::BankAccount acc;
    QCOMPARE(acc.getBalance(), 0.0);
    QCOMPARE(acc.getInterestRate(), 0.0);
}

void TestBankAccount::constructor_withValues() {
    mylib::BankAccount acc(1000.0, 0.05);
    QCOMPARE(acc.getBalance(), 1000.0);
    QCOMPARE(acc.getInterestRate(), 0.05);
}

void TestBankAccount::constructor_negativeBalance_throws() {
    QVERIFY_EXCEPTION_THROWN(mylib::BankAccount(-100.0, 0.0), std::invalid_argument);
}

// --- Пополнение ---
void TestBankAccount::deposit_positive() {
    mylib::BankAccount acc;
    acc.deposit(500.0);
    QCOMPARE(acc.getBalance(), 500.0);
}

void TestBankAccount::deposit_zero_throws() {
    mylib::BankAccount acc;
    QVERIFY_EXCEPTION_THROWN(acc.deposit(0.0), std::invalid_argument);
}

void TestBankAccount::deposit_negative_throws() {
    mylib::BankAccount acc;
    QVERIFY_EXCEPTION_THROWN(acc.deposit(-10.0), std::invalid_argument);
}

// --- Снятие ---
void TestBankAccount::withdraw_positive() {
    mylib::BankAccount acc(1000.0);
    acc.withdraw(300.0);
    QCOMPARE(acc.getBalance(), 700.0);
}

void TestBankAccount::withdraw_exactBalance_toZero() {
    mylib::BankAccount acc(500.0);
    acc.withdraw(500.0);
    QCOMPARE(acc.getBalance(), 0.0);
}

void TestBankAccount::withdraw_moreThanBalance_throws() {
    mylib::BankAccount acc(100.0);
    QVERIFY_EXCEPTION_THROWN(acc.withdraw(101.0), std::runtime_error);
}

void TestBankAccount::withdraw_negative_throws() {
    mylib::BankAccount acc(100.0);
    QVERIFY_EXCEPTION_THROWN(acc.withdraw(-50.0), std::invalid_argument);
}

// --- Проценты ---
void TestBankAccount::applyInterest_basic() {
    mylib::BankAccount acc(1000.0, 0.1); // 10%
    acc.applyInterest(2); // 1000 * 0.1 * 2 = 200
    QCOMPARE(acc.getBalance(), 1200.0);
}

void TestBankAccount::applyInterest_zeroBalance_noInterest() {
    mylib::BankAccount acc(0.0, 0.1);
    acc.applyInterest(5);
    QCOMPARE(acc.getBalance(), 0.0);
    QVERIFY(acc.getHistory().empty()); // История не должна засоряться нулевыми начислениями
}

void TestBankAccount::applyInterest_zeroRate_noInterest() {
    mylib::BankAccount acc(1000.0, 0.0);
    acc.applyInterest(5);
    QCOMPARE(acc.getBalance(), 1000.0);
}

void TestBankAccount::applyInterest_negativePeriods_throws() {
    mylib::BankAccount acc(1000.0, 0.1);
    QVERIFY_EXCEPTION_THROWN(acc.applyInterest(-1), std::invalid_argument);
}

// --- Проверка средств ---
void TestBankAccount::hasSufficientFunds_true() {
    mylib::BankAccount acc(500.0);
    QVERIFY(acc.hasSufficientFunds(500.0));
    QVERIFY(acc.hasSufficientFunds(100.0));
}

void TestBankAccount::hasSufficientFunds_false() {
    mylib::BankAccount acc(500.0);
    QVERIFY(!acc.hasSufficientFunds(501.0));
}

// --- История ---
void TestBankAccount::history_tracksOperations() {
    mylib::BankAccount acc(1000.0, 0.1);
    acc.deposit(500.0);
    acc.withdraw(200.0);
    acc.applyInterest(1); // 1300 * 0.1 = 130

    const auto& hist = acc.getHistory();
    QCOMPARE(hist.size(), 3u);
    QCOMPARE(hist[0].type, std::string("DEPOSIT"));
    QCOMPARE(hist[1].type, std::string("WITHDRAW"));
    QCOMPARE(hist[2].type, std::string("INTEREST"));
}

// --- Параметризованный тест ---
void TestBankAccount::deposit_parameterized_data() {
    QTest::addColumn<double>("initial");
    QTest::addColumn<double>("amount");
    QTest::addColumn<double>("expected");

    QTest::newRow("start0_dep100") << 0.0 << 100.0 << 100.0;
    QTest::newRow("start500_dep50") << 500.0 << 50.0 << 550.0;
    QTest::newRow("start1000_dep0.01") << 1000.0 << 0.01 << 1000.01;
}

void TestBankAccount::deposit_parameterized() {
    QFETCH(double, initial);
    QFETCH(double, amount);
    QFETCH(double, expected);

    mylib::BankAccount acc(initial);
    acc.deposit(amount);
    QCOMPARE(acc.getBalance(), expected);
}

QTEST_MAIN(TestBankAccount)
#include "test_file.moc"