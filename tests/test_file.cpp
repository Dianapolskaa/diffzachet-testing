#include "file.h"
#include <QtTest/QtTest>
#include <stdexcept>

class TestStackQueue : public QObject
{
    Q_OBJECT

private slots:
    // ===== СТЕК =====
    void stack_constructor_valid();
    void stack_constructor_invalid_throws();
    void stack_push_pop_basic();
    void stack_peek_basic();
    void stack_lifo_order();
    void stack_push_full_throws();
    void stack_pop_empty_throws();
    void stack_peek_empty_throws();
    void stack_isEmpty_isFull();
    void stack_size_capacity();
    void stack_works_after_emptied();

    // ===== ОЧЕРЕДЬ =====
    void queue_constructor_valid();
    void queue_constructor_invalid_throws();
    void queue_enqueue_dequeue_basic();
    void queue_front_basic();
    void queue_fifo_order();
    void queue_enqueue_full_throws();
    void queue_dequeue_empty_throws();
    void queue_front_empty_throws();
    void queue_isEmpty_isFull();
    void queue_size_capacity();
    void queue_works_after_emptied();

    // Параметризованные тесты
    void stack_push_pop_parameterized_data();
    void stack_push_pop_parameterized();
    void queue_enqueue_dequeue_parameterized_data();
    void queue_enqueue_dequeue_parameterized();
};

// ===== СТЕК =====
void TestStackQueue::stack_constructor_valid() {
    mylib::Stack s(5);
    QCOMPARE(s.capacity(), 5);
    QCOMPARE(s.size(), 0);
    QVERIFY(s.isEmpty());
    QVERIFY(!s.isFull());
}

void TestStackQueue::stack_constructor_invalid_throws() {
    QVERIFY_EXCEPTION_THROWN(mylib::Stack(0), std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN(mylib::Stack(-1), std::invalid_argument);
}

void TestStackQueue::stack_push_pop_basic() {
    mylib::Stack s(3);
    s.push(10);
    s.push(20);
    QCOMPARE(s.pop(), 20);
    QCOMPARE(s.pop(), 10);
}

void TestStackQueue::stack_peek_basic() {
    mylib::Stack s(3);
    s.push(42);
    QCOMPARE(s.peek(), 42);
    QCOMPARE(s.size(), 1); // peek не удаляет
}

void TestStackQueue::stack_lifo_order() {
    mylib::Stack s(5);
    s.push(1);
    s.push(2);
    s.push(3);
    QCOMPARE(s.pop(), 3);
    QCOMPARE(s.pop(), 2);
    QCOMPARE(s.pop(), 1);
}

void TestStackQueue::stack_push_full_throws() {
    mylib::Stack s(2);
    s.push(1);
    s.push(2);
    QVERIFY_EXCEPTION_THROWN(s.push(3), std::runtime_error);
}

void TestStackQueue::stack_pop_empty_throws() {
    mylib::Stack s(2);
    QVERIFY_EXCEPTION_THROWN(s.pop(), std::runtime_error);
}

void TestStackQueue::stack_peek_empty_throws() {
    mylib::Stack s(2);
    QVERIFY_EXCEPTION_THROWN(s.peek(), std::runtime_error);
}

void TestStackQueue::stack_isEmpty_isFull() {
    mylib::Stack s(2);
    QVERIFY(s.isEmpty());
    QVERIFY(!s.isFull());

    s.push(1);
    QVERIFY(!s.isEmpty());
    QVERIFY(!s.isFull());

    s.push(2);
    QVERIFY(!s.isEmpty());
    QVERIFY(s.isFull());
}

void TestStackQueue::stack_size_capacity() {
    mylib::Stack s(3);
    QCOMPARE(s.size(), 0);
    s.push(1);
    QCOMPARE(s.size(), 1);
    s.push(2);
    QCOMPARE(s.size(), 2);
    s.pop();
    QCOMPARE(s.size(), 1);
}

void TestStackQueue::stack_works_after_emptied() {
    mylib::Stack s(2);
    s.push(10);
    s.push(20);
    s.pop();
    s.pop();
    // Теперь стек пуст, но должен работать снова
    s.push(30);
    QCOMPARE(s.pop(), 30);
}

// ===== ОЧЕРЕДЬ =====
void TestStackQueue::queue_constructor_valid() {
    mylib::Queue q(5);
    QCOMPARE(q.capacity(), 5);
    QCOMPARE(q.size(), 0);
    QVERIFY(q.isEmpty());
    QVERIFY(!q.isFull());
}

void TestStackQueue::queue_constructor_invalid_throws() {
    QVERIFY_EXCEPTION_THROWN(mylib::Queue(0), std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN(mylib::Queue(-1), std::invalid_argument);
}

void TestStackQueue::queue_enqueue_dequeue_basic() {
    mylib::Queue q(3);
    q.enqueue(10);
    q.enqueue(20);
    QCOMPARE(q.dequeue(), 10);
    QCOMPARE(q.dequeue(), 20);
}

void TestStackQueue::queue_front_basic() {
    mylib::Queue q(3);
    q.enqueue(42);
    QCOMPARE(q.front(), 42);
    QCOMPARE(q.size(), 1); // front не удаляет
}

void TestStackQueue::queue_fifo_order() {
    mylib::Queue q(5);
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    QCOMPARE(q.dequeue(), 1);
    QCOMPARE(q.dequeue(), 2);
    QCOMPARE(q.dequeue(), 3);
}

void TestStackQueue::queue_enqueue_full_throws() {
    mylib::Queue q(2);
    q.enqueue(1);
    q.enqueue(2);
    QVERIFY_EXCEPTION_THROWN(q.enqueue(3), std::runtime_error);
}

void TestStackQueue::queue_dequeue_empty_throws() {
    mylib::Queue q(2);
    QVERIFY_EXCEPTION_THROWN(q.dequeue(), std::runtime_error);
}

void TestStackQueue::queue_front_empty_throws() {
    mylib::Queue q(2);
    QVERIFY_EXCEPTION_THROWN(q.front(), std::runtime_error);
}

void TestStackQueue::queue_isEmpty_isFull() {
    mylib::Queue q(2);
    QVERIFY(q.isEmpty());
    QVERIFY(!q.isFull());

    q.enqueue(1);
    QVERIFY(!q.isEmpty());
    QVERIFY(!q.isFull());

    q.enqueue(2);
    QVERIFY(!q.isEmpty());
    QVERIFY(q.isFull());
}

void TestStackQueue::queue_size_capacity() {
    mylib::Queue q(3);
    QCOMPARE(q.size(), 0);
    q.enqueue(1);
    QCOMPARE(q.size(), 1);
    q.enqueue(2);
    QCOMPARE(q.size(), 2);
    q.dequeue();
    QCOMPARE(q.size(), 1);
}

void TestStackQueue::queue_works_after_emptied() {
    mylib::Queue q(2);
    q.enqueue(10);
    q.enqueue(20);
    q.dequeue();
    q.dequeue();
    // Теперь очередь пуста, но должна работать снова
    q.enqueue(30);
    QCOMPARE(q.dequeue(), 30);
}

// ===== ПАРАМЕТРИЗОВАННЫЕ ТЕСТЫ =====
void TestStackQueue::stack_push_pop_parameterized_data() {
    QTest::addColumn<int>("capacity");
    QTest::addColumn<QList<int>>("values");
    QTest::addColumn<QList<int>>("expected_pop_order");

    QTest::newRow("single_element")
        << 1 << QList<int>{42} << QList<int>{42};

    QTest::newRow("three_elements")
        << 3 << QList<int>{1, 2, 3} << QList<int>{3, 2, 1};

    QTest::newRow("five_elements")
        << 5 << QList<int>{10, 20, 30, 40, 50} << QList<int>{50, 40, 30, 20, 10};
}

void TestStackQueue::stack_push_pop_parameterized() {
    QFETCH(int, capacity);
    QFETCH(QList<int>, values);
    QFETCH(QList<int>, expected_pop_order);

    mylib::Stack s(capacity);
    for (int v : values) {
        s.push(v);
    }
    for (int expected : expected_pop_order) {
        QCOMPARE(s.pop(), expected);
    }
}

void TestStackQueue::queue_enqueue_dequeue_parameterized_data() {
    QTest::addColumn<int>("capacity");
    QTest::addColumn<QList<int>>("values");
    QTest::addColumn<QList<int>>("expected_dequeue_order");

    QTest::newRow("single_element")
        << 1 << QList<int>{42} << QList<int>{42};

    QTest::newRow("three_elements")
        << 3 << QList<int>{1, 2, 3} << QList<int>{1, 2, 3};

    QTest::newRow("five_elements")
        << 5 << QList<int>{10, 20, 30, 40, 50} << QList<int>{10, 20, 30, 40, 50};
}

void TestStackQueue::queue_enqueue_dequeue_parameterized() {
    QFETCH(int, capacity);
    QFETCH(QList<int>, values);
    QFETCH(QList<int>, expected_dequeue_order);

    mylib::Queue q(capacity);
    for (int v : values) {
        q.enqueue(v);
    }
    for (int expected : expected_dequeue_order) {
        QCOMPARE(q.dequeue(), expected);
    }
}

QTEST_MAIN(TestStackQueue)
#include "test_file.moc"