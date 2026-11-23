#include "file.h"
#include <QtTest/QtTest>

class TestSorting : public QObject
{
    Q_OBJECT

private slots:
    // Пузырьковая
    void bubbleSort_emptyArray();
    void bubbleSort_singleElement();
    void bubbleSort_alreadySorted();
    void bubbleSort_reverseSorted();
    void bubbleSort_withDuplicates();
    void bubbleSort_ascending();
    void bubbleSort_descending();

    // Вставками
    void insertionSort_emptyArray();
    void insertionSort_singleElement();
    void insertionSort_alreadySorted();
    void insertionSort_reverseSorted();
    void insertionSort_withDuplicates();
    void insertionSort_ascending();
    void insertionSort_descending();

    // Слиянием
    void mergeSort_emptyArray();
    void mergeSort_singleElement();
    void mergeSort_alreadySorted();
    void mergeSort_reverseSorted();
    void mergeSort_withDuplicates();
    void mergeSort_ascending();
    void mergeSort_descending();

    // Параметризованные
    void bubbleSort_parameterized_data();
    void bubbleSort_parameterized();
    void insertionSort_parameterized_data();
    void insertionSort_parameterized();
    void mergeSort_parameterized_data();
    void mergeSort_parameterized();
};

// ===== Пузырьковая сортировка =====
void TestSorting::bubbleSort_emptyArray() {
    std::vector<int> arr;
    mylib::bubbleSort(arr, mylib::ascending);
    QCOMPARE(arr.size(), 0u);
}

void TestSorting::bubbleSort_singleElement() {
    std::vector<int> arr = {42};
    mylib::bubbleSort(arr, mylib::ascending);
    QCOMPARE(arr, (std::vector<int>{42}));
}

void TestSorting::bubbleSort_alreadySorted() {
    std::vector<int> arr = {1, 2, 3, 4, 5};
    mylib::bubbleSort(arr, mylib::ascending);
    QCOMPARE(arr, (std::vector<int>{1, 2, 3, 4, 5}));
}

void TestSorting::bubbleSort_reverseSorted() {
    std::vector<int> arr = {5, 4, 3, 2, 1};
    mylib::bubbleSort(arr, mylib::ascending);
    QCOMPARE(arr, (std::vector<int>{1, 2, 3, 4, 5}));
}

void TestSorting::bubbleSort_withDuplicates() {
    std::vector<int> arr = {3, 1, 2, 1, 3, 2};
    mylib::bubbleSort(arr, mylib::ascending);
    QCOMPARE(arr, (std::vector<int>{1, 1, 2, 2, 3, 3}));
}

void TestSorting::bubbleSort_ascending() {
    std::vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    mylib::bubbleSort(arr, mylib::ascending);
    QCOMPARE(arr, (std::vector<int>{11, 12, 22, 25, 34, 64, 90}));
}

void TestSorting::bubbleSort_descending() {
    std::vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    mylib::bubbleSort(arr, mylib::descending);
    QCOMPARE(arr, (std::vector<int>{90, 64, 34, 25, 22, 12, 11}));
}

// ===== Сортировка вставками =====
void TestSorting::insertionSort_emptyArray() {
    std::vector<int> arr;
    mylib::insertionSort(arr, mylib::ascending);
    QCOMPARE(arr.size(), 0u);
}

void TestSorting::insertionSort_singleElement() {
    std::vector<int> arr = {42};
    mylib::insertionSort(arr, mylib::ascending);
    QCOMPARE(arr, (std::vector<int>{42}));
}

void TestSorting::insertionSort_alreadySorted() {
    std::vector<int> arr = {1, 2, 3, 4, 5};
    mylib::insertionSort(arr, mylib::ascending);
    QCOMPARE(arr, (std::vector<int>{1, 2, 3, 4, 5}));
}

void TestSorting::insertionSort_reverseSorted() {
    std::vector<int> arr = {5, 4, 3, 2, 1};
    mylib::insertionSort(arr, mylib::ascending);
    QCOMPARE(arr, (std::vector<int>{1, 2, 3, 4, 5}));
}

void TestSorting::insertionSort_withDuplicates() {
    std::vector<int> arr = {3, 1, 2, 1, 3, 2};
    mylib::insertionSort(arr, mylib::ascending);
    QCOMPARE(arr, (std::vector<int>{1, 1, 2, 2, 3, 3}));
}

void TestSorting::insertionSort_ascending() {
    std::vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    mylib::insertionSort(arr, mylib::ascending);
    QCOMPARE(arr, (std::vector<int>{11, 12, 22, 25, 34, 64, 90}));
}

void TestSorting::insertionSort_descending() {
    std::vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    mylib::insertionSort(arr, mylib::descending);
    QCOMPARE(arr, (std::vector<int>{90, 64, 34, 25, 22, 12, 11}));
}

// ===== Сортировка слиянием =====
void TestSorting::mergeSort_emptyArray() {
    std::vector<int> arr;
    mylib::mergeSort(arr, mylib::ascending);
    QCOMPARE(arr.size(), 0u);
}

void TestSorting::mergeSort_singleElement() {
    std::vector<int> arr = {42};
    mylib::mergeSort(arr, mylib::ascending);
    QCOMPARE(arr, (std::vector<int>{42}));
}

void TestSorting::mergeSort_alreadySorted() {
    std::vector<int> arr = {1, 2, 3, 4, 5};
    mylib::mergeSort(arr, mylib::ascending);
    QCOMPARE(arr, (std::vector<int>{1, 2, 3, 4, 5}));
}

void TestSorting::mergeSort_reverseSorted() {
    std::vector<int> arr = {5, 4, 3, 2, 1};
    mylib::mergeSort(arr, mylib::ascending);
    QCOMPARE(arr, (std::vector<int>{1, 2, 3, 4, 5}));
}

void TestSorting::mergeSort_withDuplicates() {
    std::vector<int> arr = {3, 1, 2, 1, 3, 2};
    mylib::mergeSort(arr, mylib::ascending);
    QCOMPARE(arr, (std::vector<int>{1, 1, 2, 2, 3, 3}));
}

void TestSorting::mergeSort_ascending() {
    std::vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    mylib::mergeSort(arr, mylib::ascending);
    QCOMPARE(arr, (std::vector<int>{11, 12, 22, 25, 34, 64, 90}));
}

void TestSorting::mergeSort_descending() {
    std::vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    mylib::mergeSort(arr, mylib::descending);
    QCOMPARE(arr, (std::vector<int>{90, 64, 34, 25, 22, 12, 11}));
}

// ===== Параметризованные тесты =====
void TestSorting::bubbleSort_parameterized_data() {
    QTest::addColumn<std::vector<int>>("input");
    QTest::addColumn<std::vector<int>>("expected");

    QTest::newRow("two_elements") << std::vector<int>{2, 1} << std::vector<int>{1, 2};
    QTest::newRow("all_same") << std::vector<int>{5, 5, 5} << std::vector<int>{5, 5, 5};
    QTest::newRow("negative_numbers") << std::vector<int>{-3, -1, -2} << std::vector<int>{-3, -2, -1};
}

void TestSorting::bubbleSort_parameterized() {
    QFETCH(std::vector<int>, input);
    QFETCH(std::vector<int>, expected);

    mylib::bubbleSort(input, mylib::ascending);
    QCOMPARE(input, expected);
}

void TestSorting::insertionSort_parameterized_data() {
    QTest::addColumn<std::vector<int>>("input");
    QTest::addColumn<std::vector<int>>("expected");

    QTest::newRow("two_elements") << std::vector<int>{2, 1} << std::vector<int>{1, 2};
    QTest::newRow("all_same") << std::vector<int>{5, 5, 5} << std::vector<int>{5, 5, 5};
    QTest::newRow("negative_numbers") << std::vector<int>{-3, -1, -2} << std::vector<int>{-3, -2, -1};
}

void TestSorting::insertionSort_parameterized() {
    QFETCH(std::vector<int>, input);
    QFETCH(std::vector<int>, expected);

    mylib::insertionSort(input, mylib::ascending);
    QCOMPARE(input, expected);
}

void TestSorting::mergeSort_parameterized_data() {
    QTest::addColumn<std::vector<int>>("input");
    QTest::addColumn<std::vector<int>>("expected");

    QTest::newRow("two_elements") << std::vector<int>{2, 1} << std::vector<int>{1, 2};
    QTest::newRow("all_same") << std::vector<int>{5, 5, 5} << std::vector<int>{5, 5, 5};
    QTest::newRow("negative_numbers") << std::vector<int>{-3, -1, -2} << std::vector<int>{-3, -2, -1};
}

void TestSorting::mergeSort_parameterized() {
    QFETCH(std::vector<int>, input);
    QFETCH(std::vector<int>, expected);

    mylib::mergeSort(input, mylib::ascending);
    QCOMPARE(input, expected);
}

QTEST_MAIN(TestSorting)
#include "test_file.moc"