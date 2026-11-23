#include "file.h"
#include <QtTest/QtTest>
#include <stdexcept>

class TestDynamicArray : public QObject
{
    Q_OBJECT

private slots:
    // Конструкторы и правило трёх
    void constructor_default_capacity4();
    void constructor_customCapacity();
    void constructor_invalidCapacity_throws();
    void copyConstructor_deepCopy();
    void assignmentOperator_deepCopy();
    void assignmentOperator_selfAssignment();

    // pushBack и popBack
    void pushBack_basic();
    void pushBack_autoResize();
    void popBack_basic();
    void popBack_empty_throws();
    void popBack_shrinkCapacity();

    // insertAt и removeAt
    void insertAt_beginning();
    void insertAt_end();
    void insertAt_middle();
    void insertAt_invalidIndex_throws();
    void removeAt_beginning();
    void removeAt_end();
    void removeAt_middle();
    void removeAt_invalidIndex_throws();

    // get и set
    void get_validIndex();
    void get_invalidIndex_throws();
    void set_validIndex();
    void set_invalidIndex_throws();

    // indexOf и clear
    void indexOf_found();
    void indexOf_notFound();
    void clear_resetsSize();

    // Параметризованные тесты
    void pushBack_parameterized_data();
    void pushBack_parameterized();
};

// --- Конструкторы и правило трёх ---
void TestDynamicArray::constructor_default_capacity4() {
    mylib::DynamicArray arr;
    QCOMPARE(arr.size(), 0);
    QCOMPARE(arr.capacity(), 4);
}

void TestDynamicArray::constructor_customCapacity() {
    mylib::DynamicArray arr(10);
    QCOMPARE(arr.size(), 0);
    QCOMPARE(arr.capacity(), 10);
}

void TestDynamicArray::constructor_invalidCapacity_throws() {
    QVERIFY_EXCEPTION_THROWN(mylib::DynamicArray(0), std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN(mylib::DynamicArray(-5), std::invalid_argument);
}

void TestDynamicArray::copyConstructor_deepCopy() {
    mylib::DynamicArray arr1;
    arr1.pushBack(10);
    arr1.pushBack(20);

    mylib::DynamicArray arr2(arr1);
    QCOMPARE(arr2.size(), 2);
    QCOMPARE(arr2.get(0), 10);
    QCOMPARE(arr2.get(1), 20);

    // Изменяем arr1, arr2 не должен измениться
    arr1.pushBack(30);
    QCOMPARE(arr1.size(), 3);
    QCOMPARE(arr2.size(), 2);
}

void TestDynamicArray::assignmentOperator_deepCopy() {
    mylib::DynamicArray arr1;
    arr1.pushBack(10);
    arr1.pushBack(20);

    mylib::DynamicArray arr2;
    arr2 = arr1;
    QCOMPARE(arr2.size(), 2);
    QCOMPARE(arr2.get(0), 10);

    arr1.pushBack(30);
    QCOMPARE(arr1.size(), 3);
    QCOMPARE(arr2.size(), 2);
}

void TestDynamicArray::assignmentOperator_selfAssignment() {
    mylib::DynamicArray arr;
    arr.pushBack(10);
    arr = arr; // Самоприсваивание не должно упасть
    QCOMPARE(arr.size(), 1);
    QCOMPARE(arr.get(0), 10);
}

// --- pushBack и popBack ---
void TestDynamicArray::pushBack_basic() {
    mylib::DynamicArray arr;
    arr.pushBack(10);
    arr.pushBack(20);
    QCOMPARE(arr.size(), 2);
    QCOMPARE(arr.get(0), 10);
    QCOMPARE(arr.get(1), 20);
}

void TestDynamicArray::pushBack_autoResize() {
    mylib::DynamicArray arr(2); // Ёмкость = 2
    arr.pushBack(1);
    arr.pushBack(2);
    QCOMPARE(arr.capacity(), 2);
    arr.pushBack(3); // Должно увеличить ёмкость до 4
    QCOMPARE(arr.capacity(), 4);
    QCOMPARE(arr.size(), 3);
}

void TestDynamicArray::popBack_basic() {
    mylib::DynamicArray arr;
    arr.pushBack(10);
    arr.pushBack(20);
    arr.popBack();
    QCOMPARE(arr.size(), 1);
    QCOMPARE(arr.get(0), 10);
}

void TestDynamicArray::popBack_empty_throws() {
    mylib::DynamicArray arr;
    QVERIFY_EXCEPTION_THROWN(arr.popBack(), std::runtime_error);
}

void TestDynamicArray::popBack_shrinkCapacity() {
    mylib::DynamicArray arr(4);
    arr.pushBack(1);
    arr.pushBack(2);
    arr.pushBack(3);
    arr.pushBack(4);
    QCOMPARE(arr.capacity(), 4);

    arr.popBack();
    arr.popBack();
    arr.popBack(); // size = 1, capacity = 4, 1 <= 4/4 = 1 -> shrink
    QCOMPARE(arr.capacity(), 2);
}

// --- insertAt и removeAt ---
void TestDynamicArray::insertAt_beginning() {
    mylib::DynamicArray arr;
    arr.pushBack(2);
    arr.pushBack(3);
    arr.insertAt(0, 1);
    QCOMPARE(arr.get(0), 1);
    QCOMPARE(arr.get(1), 2);
    QCOMPARE(arr.get(2), 3);
}

void TestDynamicArray::insertAt_end() {
    mylib::DynamicArray arr;
    arr.pushBack(1);
    arr.insertAt(1, 2);
    QCOMPARE(arr.get(1), 2);
}

void TestDynamicArray::insertAt_middle() {
    mylib::DynamicArray arr;
    arr.pushBack(1);
    arr.pushBack(3);
    arr.insertAt(1, 2);
    QCOMPARE(arr.get(1), 2);
}

void TestDynamicArray::insertAt_invalidIndex_throws() {
    mylib::DynamicArray arr;
    arr.pushBack(1);
    QVERIFY_EXCEPTION_THROWN(arr.insertAt(-1, 5), std::out_of_range);
    QVERIFY_EXCEPTION_THROWN(arr.insertAt(5, 5), std::out_of_range);
}

void TestDynamicArray::removeAt_beginning() {
    mylib::DynamicArray arr;
    arr.pushBack(1);
    arr.pushBack(2);
    arr.pushBack(3);
    arr.removeAt(0);
    QCOMPARE(arr.get(0), 2);
    QCOMPARE(arr.size(), 2);
}

void TestDynamicArray::removeAt_end() {
    mylib::DynamicArray arr;
    arr.pushBack(1);
    arr.pushBack(2);
    arr.removeAt(1);
    QCOMPARE(arr.size(), 1);
}

void TestDynamicArray::removeAt_middle() {
    mylib::DynamicArray arr;
    arr.pushBack(1);
    arr.pushBack(2);
    arr.pushBack(3);
    arr.removeAt(1);
    QCOMPARE(arr.get(1), 3);
}

void TestDynamicArray::removeAt_invalidIndex_throws() {
    mylib::DynamicArray arr;
    arr.pushBack(1);
    QVERIFY_EXCEPTION_THROWN(arr.removeAt(-1), std::out_of_range);
    QVERIFY_EXCEPTION_THROWN(arr.removeAt(1), std::out_of_range);
}

// --- get и set ---
void TestDynamicArray::get_validIndex() {
    mylib::DynamicArray arr;
    arr.pushBack(42);
    QCOMPARE(arr.get(0), 42);
}

void TestDynamicArray::get_invalidIndex_throws() {
    mylib::DynamicArray arr;
    arr.pushBack(1);
    QVERIFY_EXCEPTION_THROWN(arr.get(-1), std::out_of_range);
    QVERIFY_EXCEPTION_THROWN(arr.get(1), std::out_of_range);
}

void TestDynamicArray::set_validIndex() {
    mylib::DynamicArray arr;
    arr.pushBack(10);
    arr.set(0, 20);
    QCOMPARE(arr.get(0), 20);
}

void TestDynamicArray::set_invalidIndex_throws() {
    mylib::DynamicArray arr;
    arr.pushBack(1);
    QVERIFY_EXCEPTION_THROWN(arr.set(-1, 5), std::out_of_range);
    QVERIFY_EXCEPTION_THROWN(arr.set(1, 5), std::out_of_range);
}

// --- indexOf и clear ---
void TestDynamicArray::indexOf_found() {
    mylib::DynamicArray arr;
    arr.pushBack(10);
    arr.pushBack(20);
    arr.pushBack(30);
    QCOMPARE(arr.indexOf(20), 1);
}

void TestDynamicArray::indexOf_notFound() {
    mylib::DynamicArray arr;
    arr.pushBack(10);
    QCOMPARE(arr.indexOf(99), -1);
}

void TestDynamicArray::clear_resetsSize() {
    mylib::DynamicArray arr;
    arr.pushBack(1);
    arr.pushBack(2);
    arr.clear();
    QCOMPARE(arr.size(), 0);
    QCOMPARE(arr.capacity(), 4); // Ёмкость не меняется
}

// --- Параметризованные тесты ---
void TestDynamicArray::pushBack_parameterized_data() {
    QTest::addColumn<int>("initialCapacity");
    QTest::addColumn<QList<int>>("values");
    QTest::addColumn<int>("expectedSize");
    QTest::addColumn<int>("expectedCapacity");

    QTest::newRow("small_array")
        << 2 << QList<int>{1, 2, 3} << 3 << 4;

    QTest::newRow("exact_capacity")
        << 3 << QList<int>{10, 20, 30} << 3 << 3;

    QTest::newRow("large_array")
        << 1 << QList<int>{1, 2, 3, 4, 5} << 5 << 8;
}

void TestDynamicArray::pushBack_parameterized() {
    QFETCH(int, initialCapacity);
    QFETCH(QList<int>, values);
    QFETCH(int, expectedSize);
    QFETCH(int, expectedCapacity);

    mylib::DynamicArray arr(initialCapacity);
    for (int v : values) {
        arr.pushBack(v);
    }
    QCOMPARE(arr.size(), expectedSize);
    QCOMPARE(arr.capacity(), expectedCapacity);
}

QTEST_MAIN(TestDynamicArray)
#include "test_file.moc"