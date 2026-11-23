#include "file.h"
#include <QtTest/QtTest>
#include <stdexcept>

class TestLinkedList : public QObject
{
    Q_OBJECT

private slots:
    // Базовые операции и размер
    void constructor_emptyList_sizeZero();
    void insertAtHead_singleElement();
    void insertAtTail_multipleElements();
    void insertAtIndex_validPosition();

    // Негативные: некорректные индексы
    void insertAtIndex_negative_throws();
    void insertAtIndex_tooLarge_throws();
    void get_invalidIndex_throws();

    // Удаление и поиск
    void removeByValue_exists_true();
    void removeByValue_notExists_false();
    void removeByValue_duplicates_removesFirst();
    void removeByValue_headElement();
    void indexOf_found();
    void indexOf_notFound();

    // Граничные случаи
    void clear_nonEmptyList_becomesEmpty();
    void insertAfterClear_works();

    // Параметризованный тест
    void insertAtIndex_parameterized_data();
    void insertAtIndex_parameterized();
};

// --- Базовые операции ---
void TestLinkedList::constructor_emptyList_sizeZero() {
    mylib::LinkedList list;
    QCOMPARE(list.size(), 0);
}

void TestLinkedList::insertAtHead_singleElement() {
    mylib::LinkedList list;
    list.insertAtHead(10);
    QCOMPARE(list.size(), 1);
    QCOMPARE(list.get(0), 10);
}

void TestLinkedList::insertAtTail_multipleElements() {
    mylib::LinkedList list;
    list.insertAtTail(1);
    list.insertAtTail(2);
    list.insertAtTail(3);
    QCOMPARE(list.get(0), 1);
    QCOMPARE(list.get(2), 3);
}

void TestLinkedList::insertAtIndex_validPosition() {
    mylib::LinkedList list;
    list.insertAtTail(1);
    list.insertAtTail(3);
    list.insertAtIndex(1, 2); // Вставляем между 1 и 3
    QCOMPARE(list.get(1), 2);
    QCOMPARE(list.size(), 3);
}

// --- Негативные ---
void TestLinkedList::insertAtIndex_negative_throws() {
    mylib::LinkedList list;
    QVERIFY_EXCEPTION_THROWN(list.insertAtIndex(-1, 5), std::out_of_range);
}

void TestLinkedList::insertAtIndex_tooLarge_throws() {
    mylib::LinkedList list;
    list.insertAtTail(1);
    QVERIFY_EXCEPTION_THROWN(list.insertAtIndex(5, 5), std::out_of_range);
}

void TestLinkedList::get_invalidIndex_throws() {
    mylib::LinkedList list;
    list.insertAtTail(10);
    QVERIFY_EXCEPTION_THROWN(list.get(1), std::out_of_range);
    QVERIFY_EXCEPTION_THROWN(list.get(-1), std::out_of_range);
}

// --- Удаление и поиск ---
void TestLinkedList::removeByValue_exists_true() {
    mylib::LinkedList list;
    list.insertAtTail(10);
    list.insertAtTail(20);
    QVERIFY(list.removeByValue(10));
    QCOMPARE(list.size(), 1);
    QCOMPARE(list.get(0), 20);
}

void TestLinkedList::removeByValue_notExists_false() {
    mylib::LinkedList list;
    list.insertAtTail(10);
    QVERIFY(!list.removeByValue(99));
    QCOMPARE(list.size(), 1);
}

void TestLinkedList::removeByValue_duplicates_removesFirst() {
    mylib::LinkedList list;
    list.insertAtTail(5);
    list.insertAtTail(5);
    list.insertAtTail(5);
    list.removeByValue(5);
    QCOMPARE(list.size(), 2);
    QCOMPARE(list.get(0), 5); // Первый 5 удалён, но следующие остались
}

void TestLinkedList::removeByValue_headElement() {
    mylib::LinkedList list;
    list.insertAtHead(100);
    list.insertAtHead(200);
    list.removeByValue(200); // Удаляем голову
    QCOMPARE(list.get(0), 100);
}

void TestLinkedList::indexOf_found() {
    mylib::LinkedList list;
    list.insertAtTail(10);
    list.insertAtTail(20);
    QCOMPARE(list.indexOf(20), 1);
}

void TestLinkedList::indexOf_notFound() {
    mylib::LinkedList list;
    list.insertAtTail(10);
    QCOMPARE(list.indexOf(99), -1);
}

// --- Граничные случаи ---
void TestLinkedList::clear_nonEmptyList_becomesEmpty() {
    mylib::LinkedList list;
    list.insertAtTail(1);
    list.insertAtTail(2);
    list.clear();
    QCOMPARE(list.size(), 0);
}

void TestLinkedList::insertAfterClear_works() {
    mylib::LinkedList list;
    list.insertAtTail(1);
    list.clear();
    list.insertAtTail(2); // Не должно упасть
    QCOMPARE(list.get(0), 2);
}

// --- Параметризованный тест ---
void TestLinkedList::insertAtIndex_parameterized_data() {
    QTest::addColumn<int>("initialSize");
    QTest::addColumn<int>("insertIndex");
    QTest::addColumn<int>("value");
    QTest::addColumn<int>("expectedSize");

    QTest::newRow("insert_at_0_empty") << 0 << 0 << 10 << 1;
    QTest::newRow("insert_at_end") << 2 << 2 << 30 << 3;
    QTest::newRow("insert_in_middle") << 3 << 1 << 99 << 4;
    QTest::newRow("insert_at_0_nonEmpty") << 2 << 0 << 5 << 3;
}

void TestLinkedList::insertAtIndex_parameterized() {
    QFETCH(int, initialSize);
    QFETCH(int, insertIndex);
    QFETCH(int, value);
    QFETCH(int, expectedSize);

    mylib::LinkedList list;
    for (int i = 0; i < initialSize; ++i) {
        list.insertAtTail(i);
    }

    list.insertAtIndex(insertIndex, value);
    QCOMPARE(list.size(), expectedSize);
    QCOMPARE(list.get(insertIndex), value);
}

QTEST_MAIN(TestLinkedList)
#include "test_file.moc"