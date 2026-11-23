#include "file.h"
#include <QtTest/QtTest>

class TestRoman : public QObject
{
    Q_OBJECT

private slots:
    // Позитивные: базовые конвертации
    void intToRoman_singleDigit();
    void intToRoman_teens();
    void intToRoman_tens();
    void intToRoman_hundreds();
    void intToRoman_thousands();

    // Позитивные: вычитающие комбинации
    void intToRoman_subtractiveCombinations();

    // Границы диапазона
    void intToRoman_minValue();
    void intToRoman_maxValue();

    // Негативные: вне диапазона
    void intToRoman_zero();
    void intToRoman_negative();
    void intToRoman_tooLarge();

    // Обратная конвертация
    void romanToInt_basic();
    void romanToInt_subtractive();
    void romanToInt_complex();

    // Негативные: невалидные строки
    void romanToInt_emptyString();
    void romanToInt_invalidCharacters();
    void romanToInt_invalidSubtraction();

    // Параметризованный тест: двусторонняя конвертация
    void roundTrip_data();
    void roundTrip();

    // Проверка валидности
    void isValidRoman_valid();
    void isValidRoman_invalid();
};

// --- intToRoman ---
void TestRoman::intToRoman_singleDigit() {
    QCOMPARE(mylib::intToRoman(1), std::string("I"));
    QCOMPARE(mylib::intToRoman(3), std::string("III"));
    QCOMPARE(mylib::intToRoman(5), std::string("V"));
}

void TestRoman::intToRoman_teens() {
    QCOMPARE(mylib::intToRoman(4), std::string("IV"));
    QCOMPARE(mylib::intToRoman(9), std::string("IX"));
    QCOMPARE(mylib::intToRoman(14), std::string("XIV"));
}

void TestRoman::intToRoman_tens() {
    QCOMPARE(mylib::intToRoman(40), std::string("XL"));
    QCOMPARE(mylib::intToRoman(90), std::string("XC"));
    QCOMPARE(mylib::intToRoman(99), std::string("XCIX"));
}

void TestRoman::intToRoman_hundreds() {
    QCOMPARE(mylib::intToRoman(400), std::string("CD"));
    QCOMPARE(mylib::intToRoman(900), std::string("CM"));
    QCOMPARE(mylib::intToRoman(999), std::string("CMXCIX"));
}

void TestRoman::intToRoman_thousands() {
    QCOMPARE(mylib::intToRoman(1000), std::string("M"));
    QCOMPARE(mylib::intToRoman(3000), std::string("MMM"));
}

void TestRoman::intToRoman_subtractiveCombinations() {
    QCOMPARE(mylib::intToRoman(4), std::string("IV"));
    QCOMPARE(mylib::intToRoman(9), std::string("IX"));
    QCOMPARE(mylib::intToRoman(40), std::string("XL"));
    QCOMPARE(mylib::intToRoman(90), std::string("XC"));
    QCOMPARE(mylib::intToRoman(400), std::string("CD"));
    QCOMPARE(mylib::intToRoman(900), std::string("CM"));
}

void TestRoman::intToRoman_minValue() {
    QCOMPARE(mylib::intToRoman(1), std::string("I"));
}

void TestRoman::intToRoman_maxValue() {
    QCOMPARE(mylib::intToRoman(3999), std::string("MMMCMXCIX"));
}

void TestRoman::intToRoman_zero() {
    QCOMPARE(mylib::intToRoman(0), std::string(""));
}

void TestRoman::intToRoman_negative() {
    QCOMPARE(mylib::intToRoman(-5), std::string(""));
}

void TestRoman::intToRoman_tooLarge() {
    QCOMPARE(mylib::intToRoman(4000), std::string(""));
}

// --- romanToInt ---
void TestRoman::romanToInt_basic() {
    QCOMPARE(mylib::romanToInt("I"), 1);
    QCOMPARE(mylib::romanToInt("V"), 5);
    QCOMPARE(mylib::romanToInt("X"), 10);
    QCOMPARE(mylib::romanToInt("L"), 50);
    QCOMPARE(mylib::romanToInt("C"), 100);
    QCOMPARE(mylib::romanToInt("D"), 500);
    QCOMPARE(mylib::romanToInt("M"), 1000);
}

void TestRoman::romanToInt_subtractive() {
    QCOMPARE(mylib::romanToInt("IV"), 4);
    QCOMPARE(mylib::romanToInt("IX"), 9);
    QCOMPARE(mylib::romanToInt("XL"), 40);
    QCOMPARE(mylib::romanToInt("XC"), 90);
    QCOMPARE(mylib::romanToInt("CD"), 400);
    QCOMPARE(mylib::romanToInt("CM"), 900);
}

void TestRoman::romanToInt_complex() {
    QCOMPARE(mylib::romanToInt("XIV"), 14);
    QCOMPARE(mylib::romanToInt("XCIX"), 99);
    QCOMPARE(mylib::romanToInt("CMXCIX"), 999);
    QCOMPARE(mylib::romanToInt("MMMCMXCIX"), 3999);
}

void TestRoman::romanToInt_emptyString() {
    QCOMPARE(mylib::romanToInt(""), 0);
}

void TestRoman::romanToInt_invalidCharacters() {
    QCOMPARE(mylib::romanToInt("ABC"), 0);
    QCOMPARE(mylib::romanToInt("IIII"), 0); // Невалидно: 4 I подряд
}

void TestRoman::romanToInt_invalidSubtraction() {
    QCOMPARE(mylib::romanToInt("IC"), 0); // Невалидно: I перед C
    QCOMPARE(mylib::romanToInt("IL"), 0); // Невалидно: I перед L
}

// --- Параметризованный тест ---
void TestRoman::roundTrip_data() {
    QTest::addColumn<int>("arabic");
    QTest::addColumn<std::string>("roman");

    QTest::newRow("1") << 1 << std::string("I");
    QTest::newRow("4") << 4 << std::string("IV");
    QTest::newRow("9") << 9 << std::string("IX");
    QTest::newRow("14") << 14 << std::string("XIV");
    QTest::newRow("40") << 40 << std::string("XL");
    QTest::newRow("90") << 90 << std::string("XC");
    QTest::newRow("99") << 99 << std::string("XCIX");
    QTest::newRow("400") << 400 << std::string("CD");
    QTest::newRow("900") << 900 << std::string("CM");
    QTest::newRow("999") << 999 << std::string("CMXCIX");
    QTest::newRow("3999") << 3999 << std::string("MMMCMXCIX");
}

void TestRoman::roundTrip() {
    QFETCH(int, arabic);
    QFETCH(std::string, roman);

    QCOMPARE(mylib::intToRoman(arabic), roman);
    QCOMPARE(mylib::romanToInt(roman), arabic);
}

// --- isValidRoman ---
void TestRoman::isValidRoman_valid() {
    QVERIFY(mylib::isValidRoman("I"));
    QVERIFY(mylib::isValidRoman("IV"));
    QVERIFY(mylib::isValidRoman("IX"));
    QVERIFY(mylib::isValidRoman("XL"));
    QVERIFY(mylib::isValidRoman("XC"));
    QVERIFY(mylib::isValidRoman("CD"));
    QVERIFY(mylib::isValidRoman("CM"));
    QVERIFY(mylib::isValidRoman("MMMCMXCIX"));
}

void TestRoman::isValidRoman_invalid() {
    QVERIFY(!mylib::isValidRoman(""));
    QVERIFY(!mylib::isValidRoman("IIII"));
    QVERIFY(!mylib::isValidRoman("IC"));
    QVERIFY(!mylib::isValidRoman("IL"));
    QVERIFY(!mylib::isValidRoman("ABC"));
    QVERIFY(!mylib::isValidRoman("VV"));
}

QTEST_MAIN(TestRoman)
#include "test_file.moc"