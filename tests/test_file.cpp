#include "file.h"
#include <QtTest/QtTest>

class TestStringAnalyzer : public QObject
{
    Q_OBJECT

private slots:
    // countWords
    void countWords_emptyString_0();
    void countWords_onlySpaces_0();
    void countWords_normalString_correct();
    void countWords_multipleDelimiters_correct();

    // countCharOccurrences
    void countCharOccurrences_found();
    void countCharOccurrences_notFound();
    void countCharOccurrences_emptyString_0();

    // mostFrequentLetter
    void mostFrequentLetter_normalString();
    void mostFrequentLetter_noLetters_returnsNull();
    void mostFrequentLetter_allSame();

    // longestStringLength
    void longestStringLength_emptyArray_0();
    void longestStringLength_normalArray();
    void longestStringLength_arrayWithEmptyStrings();

    // Параметризованный тест для countWords
    void countWords_parameterized_data();
    void countWords_parameterized();
};

// --- countWords ---
void TestStringAnalyzer::countWords_emptyString_0() {
    QCOMPARE(mylib::countWords(""), 0);
}

void TestStringAnalyzer::countWords_onlySpaces_0() {
    QCOMPARE(mylib::countWords("   \t  "), 0);
}

void TestStringAnalyzer::countWords_normalString_correct() {
    QCOMPARE(mylib::countWords("hello world"), 2);
}

void TestStringAnalyzer::countWords_multipleDelimiters_correct() {
    // Пробелы и табуляции подряд, плюс пробелы в начале и конце
    QCOMPARE(mylib::countWords("  hello \t\t world  "), 2);
}

// --- countCharOccurrences ---
void TestStringAnalyzer::countCharOccurrences_found() {
    QCOMPARE(mylib::countCharOccurrences("banana", 'a'), 3);
}

void TestStringAnalyzer::countCharOccurrences_notFound() {
    QCOMPARE(mylib::countCharOccurrences("apple", 'z'), 0);
}

void TestStringAnalyzer::countCharOccurrences_emptyString_0() {
    QCOMPARE(mylib::countCharOccurrences("", 'a'), 0);
}

// --- mostFrequentLetter ---
void TestStringAnalyzer::mostFrequentLetter_normalString() {
    QCOMPARE(mylib::mostFrequentLetter("hello world"), 'l');
}

void TestStringAnalyzer::mostFrequentLetter_noLetters_returnsNull() {
    // Только цифры и пробелы
    QCOMPARE(mylib::mostFrequentLetter("123 456"), '\0');
}

void TestStringAnalyzer::mostFrequentLetter_allSame() {
    QCOMPARE(mylib::mostFrequentLetter("aaaa"), 'a');
}

// --- longestStringLength ---
void TestStringAnalyzer::longestStringLength_emptyArray_0() {
    std::vector<std::string> arr;
    QCOMPARE(mylib::longestStringLength(arr), 0u);
}

void TestStringAnalyzer::longestStringLength_normalArray() {
    std::vector<std::string> arr = {"hi", "hello", "hey"};
    QCOMPARE(mylib::longestStringLength(arr), 5u);
}

void TestStringAnalyzer::longestStringLength_arrayWithEmptyStrings() {
    std::vector<std::string> arr = {"", "", "a", ""};
    QCOMPARE(mylib::longestStringLength(arr), 1u);
}

// --- Параметризованный тест ---
void TestStringAnalyzer::countWords_parameterized_data() {
    QTest::addColumn<std::string>("input");
    QTest::addColumn<int>("expected");

    QTest::newRow("single_word") << std::string("word") << 1;
    QTest::newRow("tabs_and_spaces") << std::string("\tword1 \t word2\t") << 2;
    QTest::newRow("punctuation_attached") << std::string("hello,world!") << 1; // Знаки препинания не разделяют слова
    QTest::newRow("mixed_whitespace") << std::string("a b  c   d") << 4;
}

void TestStringAnalyzer::countWords_parameterized() {
    QFETCH(std::string, input);
    QFETCH(int, expected);
    QCOMPARE(mylib::countWords(input), expected);
}

QTEST_MAIN(TestStringAnalyzer)
#include "test_file.moc"