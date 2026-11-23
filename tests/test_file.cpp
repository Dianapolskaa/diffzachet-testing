#include "file.h"
#include <QtTest/QtTest>

class TestValidator : public QObject
{
    Q_OBJECT

private slots:
    // Email
    void isValidEmail_valid();
    void isValidEmail_emptyString();
    void isValidEmail_noAt();
    void isValidEmail_twoAt();
    void isValidEmail_noDomain();
    void isValidEmail_domainStartsWithDot();
    void isValidEmail_noTldLetter();

    // Телефон
    void isValidPhone_validFormats();
    void isValidPhone_emptyString();
    void isValidPhone_invalidChars();
    void isValidPhone_tooShort();
    void isValidPhone_tooLong();
    void isValidPhone_wrongCountryCode();

    // Пароль
    void isValidPassword_valid();
    void isValidPassword_tooShort();
    void isValidPassword_noLetter();
    void isValidPassword_noDigit();
    void isValidPassword_noSpecial();
    void isValidPassword_boundaryLength();

    // Возраст
    void isValidAge_valid();
    void isValidAge_zero();
    void isValidAge_boundary150();
    void isValidAge_negative();
    void isValidAge_tooLarge();

    // Параметризованные тесты
    void email_parameterized_data();
    void email_parameterized();
    void phone_parameterized_data();
    void phone_parameterized();
    void password_parameterized_data();
    void password_parameterized();
};

// --- Email ---
void TestValidator::isValidEmail_valid() {
    QVERIFY(mylib::isValidEmail("user@example.com"));
    QVERIFY(mylib::isValidEmail("john.doe+test@sub.domain.co.uk"));
}

void TestValidator::isValidEmail_emptyString() {
    QVERIFY(!mylib::isValidEmail(""));
}

void TestValidator::isValidEmail_noAt() {
    QVERIFY(!mylib::isValidEmail("userexample.com"));
}

void TestValidator::isValidEmail_twoAt() {
    QVERIFY(!mylib::isValidEmail("user@@example.com"));
    QVERIFY(!mylib::isValidEmail("user@name@example.com"));
}

void TestValidator::isValidEmail_noDomain() {
    QVERIFY(!mylib::isValidEmail("user@"));
    QVERIFY(!mylib::isValidEmail("@example.com"));
}

void TestValidator::isValidEmail_domainStartsWithDot() {
    QVERIFY(!mylib::isValidEmail("user@.example.com"));
    QVERIFY(!mylib::isValidEmail("user@example.com."));
}

void TestValidator::isValidEmail_noTldLetter() {
    QVERIFY(!mylib::isValidEmail("user@example.123"));
}

// --- Телефон ---
void TestValidator::isValidPhone_validFormats() {
    QVERIFY(mylib::isValidPhone("+7(999)123-45-67"));
    QVERIFY(mylib::isValidPhone("8-999-123-45-67"));
    QVERIFY(mylib::isValidPhone("9991234567"));
    QVERIFY(mylib::isValidPhone("+7 999 123 45 67"));
}

void TestValidator::isValidPhone_emptyString() {
    QVERIFY(!mylib::isValidPhone(""));
}

void TestValidator::isValidPhone_invalidChars() {
    QVERIFY(!mylib::isValidPhone("+7(999)123-45-67a"));
    QVERIFY(!mylib::isValidPhone("8999123456!"));
}

void TestValidator::isValidPhone_tooShort() {
    QVERIFY(!mylib::isValidPhone("12345"));
}

void TestValidator::isValidPhone_tooLong() {
    QVERIFY(!mylib::isValidPhone("+7999123456789"));
}

void TestValidator::isValidPhone_wrongCountryCode() {
    QVERIFY(!mylib::isValidPhone("+19991234567"));
    QVERIFY(!mylib::isValidPhone("+59991234567"));
}

// --- Пароль ---
void TestValidator::isValidPassword_valid() {
    QVERIFY(mylib::isValidPassword("Strong1!"));
    QVERIFY(mylib::isValidPassword("MyP@ssw0rd_2026"));
}

void TestValidator::isValidPassword_tooShort() {
    QVERIFY(!mylib::isValidPassword("Ab1!"));
}

void TestValidator::isValidPassword_noLetter() {
    QVERIFY(!mylib::isValidPassword("12345678!@"));
}

void TestValidator::isValidPassword_noDigit() {
    QVERIFY(!mylib::isValidPassword("Abcdefgh!@"));
}

void TestValidator::isValidPassword_noSpecial() {
    QVERIFY(!mylib::isValidPassword("Abcdefgh12"));
}

void TestValidator::isValidPassword_boundaryLength() {
    // Ровно 8 символов — валидно
    QVERIFY(mylib::isValidPassword("Abcdef1!"));
    // 7 символов — невалидно
    QVERIFY(!mylib::isValidPassword("Abcd1!"));
}

// --- Возраст ---
void TestValidator::isValidAge_valid() {
    QVERIFY(mylib::isValidAge(25));
    QVERIFY(mylib::isValidAge(100));
}

void TestValidator::isValidAge_zero() {
    QVERIFY(mylib::isValidAge(0));
}

void TestValidator::isValidAge_boundary150() {
    QVERIFY(mylib::isValidAge(150));
}

void TestValidator::isValidAge_negative() {
    QVERIFY(!mylib::isValidAge(-1));
    QVERIFY(!mylib::isValidAge(-100));
}

void TestValidator::isValidAge_tooLarge() {
    QVERIFY(!mylib::isValidAge(151));
    QVERIFY(!mylib::isValidAge(200));
}

// --- Параметризованные тесты ---
void TestValidator::email_parameterized_data() {
    QTest::addColumn<std::string>("email");
    QTest::addColumn<bool>("expected");

    QTest::newRow("valid_simple") << std::string("a@b.com") << true;
    QTest::newRow("valid_complex") << std::string("user.name+tag@domain.co.uk") << true;
    QTest::newRow("invalid_empty") << std::string("") << false;
    QTest::newRow("invalid_no_at") << std::string("userdomain.com") << false;
    QTest::newRow("invalid_two_at") << std::string("a@b@c.com") << false;
    QTest::newRow("invalid_no_domain") << std::string("user@") << false;
    QTest::newRow("invalid_start_dot") << std::string("user@.com") << false;
}

void TestValidator::email_parameterized() {
    QFETCH(std::string, email);
    QFETCH(bool, expected);
    QCOMPARE(mylib::isValidEmail(email), expected);
}

void TestValidator::phone_parameterized_data() {
    QTest::addColumn<std::string>("phone");
    QTest::addColumn<bool>("expected");

    QTest::newRow("valid_plus7") << std::string("+79991234567") << true;
    QTest::newRow("valid_8") << std::string("89991234567") << true;
    QTest::newRow("valid_10digits") << std::string("9991234567") << true;
    QTest::newRow("invalid_short") << std::string("12345") << false;
    QTest::newRow("invalid_long") << std::string("+799912345678") << false;
    QTest::newRow("invalid_country") << std::string("+19991234567") << false;
}

void TestValidator::phone_parameterized() {
    QFETCH(std::string, phone);
    QFETCH(bool, expected);
    QCOMPARE(mylib::isValidPhone(phone), expected);
}

void TestValidator::password_parameterized_data() {
    QTest::addColumn<std::string>("password");
    QTest::addColumn<bool>("expected");

    QTest::newRow("valid_min") << std::string("Abcdef1!") << true;
    QTest::newRow("valid_long") << std::string("MyP@ssw0rd_2026") << true;
    QTest::newRow("invalid_short") << std::string("Ab1!") << false;
    QTest::newRow("invalid_no_special") << std::string("Abcdefgh12") << false;
    QTest::newRow("invalid_no_digit") << std::string("Abcdefgh!@") << false;
    QTest::newRow("invalid_no_letter") << std::string("12345678!@") << false;
}

void TestValidator::password_parameterized() {
    QFETCH(std::string, password);
    QFETCH(bool, expected);
    QCOMPARE(mylib::isValidPassword(password), expected);
}

QTEST_MAIN(TestValidator)
#include "test_file.moc"