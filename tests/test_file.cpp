#include "file.h"
#include <QtTest/QtTest>

class TestStrings : public QObject
{
    Q_OBJECT

private slots:
    // stringLength
    void stringLength_emptyString();
    void stringLength_singleChar();
    void stringLength_normalString();

    // concatenate
    void concatenate_twoStrings();
    void concatenate_emptyStrings();
    void concatenate_oneEmpty();

    // reverse
    void reverse_emptyString();
    void reverse_singleChar();
    void reverse_normalString();
    void reverse_palindrome();

    // toUpperCase / toLowerCase (параметризованные)
    void caseConversion_data();
    void caseConversion();

    // findSubstring
    void findSubstring_found();
    void findSubstring_notFound();
    void findSubstring_emptySubstring();
    void findSubstring_substringLongerThanString();
    void findSubstring_atBeginning();
    void findSubstring_atEnd();

    // split (параметризованные)
    void split_data();
    void split();

    // Граничные случаи split
    void split_delimiterAtStart();
    void split_delimiterAtEnd();
    void split_multipleDelimiters();
    void split_onlyDelimiters();
};

// --- stringLength ---
void TestStrings::stringLength_emptyString() {
    QCOMPARE(mylib::stringLength(""), 0u);
}

void TestStrings::stringLength_singleChar() {
    QCOMPARE(mylib::stringLength("a"), 1u);
}

void TestStrings::stringLength_normalString() {
    QCOMPARE(mylib::stringLength("hello"), 5u);
}

// --- concatenate ---
void TestStrings::concatenate_twoStrings() {
    QCOMPARE(mylib::concatenate("hello", " world"), std::string("hello world"));
}

void TestStrings::concatenate_emptyStrings() {
    QCOMPARE(mylib::concatenate("", ""), std::string(""));
}

void TestStrings::concatenate_oneEmpty() {
    QCOMPARE(mylib::concatenate("hello", ""), std::string("hello"));
    QCOMPARE(mylib::concatenate("", "world"), std::string("world"));
}

// --- reverse ---
void TestStrings::reverse_emptyString() {
    QCOMPARE(mylib::reverse(""), std::string(""));
}

void TestStrings::reverse_singleChar() {
    QCOMPARE(mylib::reverse("a"), std::string("a"));
}

void TestStrings::reverse_normalString() {
    QCOMPARE(mylib::reverse("hello"), std::string("olleh"));
}

void TestStrings::reverse_palindrome() {
    QCOMPARE(mylib::reverse("madam"), std::string("madam"));
}

// --- caseConversion (параметризованный) ---
void TestStrings::caseConversion_data() {
    QTest::addColumn<std::string>("input");
    QTest::addColumn<std::string>("upper");
    QTest::addColumn<std::string>("lower");

    QTest::newRow("hello") << std::string("hello") << std::string("HELLO") << std::string("hello");
    QTest::newRow("WORLD") << std::string("WORLD") << std::string("WORLD") << std::string("world");
    QTest::newRow("MiXeD") << std::string("MiXeD") << std::string("MIXED") << std::string("mixed");
    QTest::newRow("empty") << std::string("") << std::string("") << std::string("");
    QTest::newRow("numbers123") << std::string("abc123") << std::string("ABC123") << std::string("abc123");
}

void TestStrings::caseConversion() {
    QFETCH(std::string, input);
    QFETCH(std::string, upper);
    QFETCH(std::string, lower);

    QCOMPARE(mylib::toUpperCase(input), upper);
    QCOMPARE(mylib::toLowerCase(input), lower);
}

// --- findSubstring ---
void TestStrings::findSubstring_found() {
    QCOMPARE(mylib::findSubstring("hello world", "world"), 6);
}

void TestStrings::findSubstring_notFound() {
    QCOMPARE(mylib::findSubstring("hello", "xyz"), -1);
}

void TestStrings::findSubstring_emptySubstring() {
    QCOMPARE(mylib::findSubstring("hello", ""), 0);
}

void TestStrings::findSubstring_substringLongerThanString() {
    QCOMPARE(mylib::findSubstring("hi", "hello"), -1);
}

void TestStrings::findSubstring_atBeginning() {
    QCOMPARE(mylib::findSubstring("hello world", "hello"), 0);
}

void TestStrings::findSubstring_atEnd() {
    QCOMPARE(mylib::findSubstring("hello world", "world"), 6);
}

// --- split (параметризованный) ---
void TestStrings::split_data() {
    QTest::addColumn<std::string>("input");
    QTest::addColumn<char>("delimiter");
    QTest::addColumn<std::vector<std::string>>("expected");

    QTest::newRow("simple")
        << std::string("a,b,c") << ','
        << std::vector<std::string>{"a", "b", "c"};

    QTest::newRow("noDelimiter")
        << std::string("hello") << ','
        << std::vector<std::string>{"hello"};

    QTest::newRow("emptyString")
        << std::string("") << ','
        << std::vector<std::string>{};
}

void TestStrings::split() {
    QFETCH(std::string, input);
    QFETCH(char, delimiter);
    QFETCH(std::vector<std::string>, expected);

    QCOMPARE(mylib::split(input, delimiter), expected);
}

// --- Граничные случаи split ---
void TestStrings::split_delimiterAtStart() {
    auto result = mylib::split(",a,b", ',');
    QCOMPARE(result.size(), 3u);
    QCOMPARE(result[0], std::string(""));
    QCOMPARE(result[1], std::string("a"));
    QCOMPARE(result[2], std::string("b"));
}

void TestStrings::split_delimiterAtEnd() {
    auto result = mylib::split("a,b,", ',');
    QCOMPARE(result.size(), 3u);
    QCOMPARE(result[0], std::string("a"));
    QCOMPARE(result[1], std::string("b"));
    QCOMPARE(result[2], std::string(""));
}

void TestStrings::split_multipleDelimiters() {
    auto result = mylib::split("a,,b", ',');
    QCOMPARE(result.size(), 3u);
    QCOMPARE(result[0], std::string("a"));
    QCOMPARE(result[1], std::string(""));
    QCOMPARE(result[2], std::string("b"));
}

void TestStrings::split_onlyDelimiters() {
    auto result = mylib::split(",,,", ',');
    QCOMPARE(result.size(), 4u);
    for (const auto& s : result) {
        QCOMPARE(s, std::string(""));
    }
}

QTEST_MAIN(TestStrings)
#include "test_file.moc"