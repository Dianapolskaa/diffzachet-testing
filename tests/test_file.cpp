#include "file.h"
#include <QtTest/QtTest>
#include <cmath>

class TestRectangle : public QObject
{
    Q_OBJECT

private slots:
    // area
    void area_normal_positive();
    void area_zeroWidth_zero();
    void area_negativeDimensions_zero();

    // contains
    void contains_inside_true();
    void contains_onBoundary_true();
    void contains_outside_false();
    void contains_negativeSizeRect_false();

    // intersects
    void intersects_overlapping_true();
    void intersects_touchingEdges_false(); // Граничный случай: касание
    void intersects_nested_true();
    void intersects_disjoint_false();

    // boundingBox
    void boundingBox_disjoint_correct();
    void boundingBox_overlapping_correct();

    // getIntersection
    void getIntersection_valid_updatesOut();
    void getIntersection_touching_returnsFalse();

    // Параметризованный тест для contains
    void contains_parameterized_data();
    void contains_parameterized();
};

// --- area ---
void TestRectangle::area_normal_positive() {
    QCOMPARE(mylib::area({0, 0, 10, 5}), 50.0);
}

void TestRectangle::area_zeroWidth_zero() {
    QCOMPARE(mylib::area({0, 0, 0, 5}), 0.0);
}

void TestRectangle::area_negativeDimensions_zero() {
    QCOMPARE(mylib::area({0, 0, -5, 5}), 0.0);
}

// --- contains ---
void TestRectangle::contains_inside_true() {
    QVERIFY(mylib::contains({0, 0, 10, 10}, 5, 5));
}

void TestRectangle::contains_onBoundary_true() {
    // Точка на границе
    QVERIFY(mylib::contains({0, 0, 10, 10}, 10, 10));
    QVERIFY(mylib::contains({0, 0, 10, 10}, 0, 0));
}

void TestRectangle::contains_outside_false() {
    QVERIFY(!mylib::contains({0, 0, 10, 10}, 11, 5));
}

void TestRectangle::contains_negativeSizeRect_false() {
    QVERIFY(!mylib::contains({0, 0, -10, 10}, 5, 5));
}

// --- intersects ---
void TestRectangle::intersects_overlapping_true() {
    QVERIFY(mylib::intersects({0, 0, 10, 10}, {5, 5, 10, 10}));
}

void TestRectangle::intersects_touchingEdges_false() {
    // Касание правым краем левого (площадь пересечения = 0)
    QVERIFY(!mylib::intersects({0, 0, 10, 10}, {10, 0, 10, 10}));
}

void TestRectangle::intersects_nested_true() {
    // Один полностью внутри другого
    QVERIFY(mylib::intersects({0, 0, 20, 20}, {5, 5, 5, 5}));
}

void TestRectangle::intersects_disjoint_false() {
    QVERIFY(!mylib::intersects({0, 0, 5, 5}, {10, 10, 5, 5}));
}

// --- boundingBox ---
void TestRectangle::boundingBox_disjoint_correct() {
    auto box = mylib::boundingBox({0, 0, 5, 5}, {10, 10, 5, 5});
    QCOMPARE(box.x, 0.0);
    QCOMPARE(box.y, 0.0);
    QCOMPARE(box.width, 15.0);
    QCOMPARE(box.height, 15.0);
}

void TestRectangle::boundingBox_overlapping_correct() {
    auto box = mylib::boundingBox({0, 0, 10, 10}, {5, 5, 10, 10});
    QCOMPARE(box.width, 15.0);
    QCOMPARE(box.height, 15.0);
}

// --- getIntersection ---
void TestRectangle::getIntersection_valid_updatesOut() {
    mylib::Rectangle out;
    bool res = mylib::getIntersection({0, 0, 10, 10}, {5, 5, 10, 10}, out);
    QVERIFY(res);
    QCOMPARE(out.x, 5.0);
    QCOMPARE(out.y, 5.0);
    QCOMPARE(out.width, 5.0);
    QCOMPARE(out.height, 5.0);
}

void TestRectangle::getIntersection_touching_returnsFalse() {
    mylib::Rectangle out = {99, 99, 99, 99}; // Мусорные значения
    bool res = mylib::getIntersection({0, 0, 10, 10}, {10, 0, 10, 10}, out);
    QVERIFY(!res);
    // out не должен был измениться
    QCOMPARE(out.x, 99.0);
}

// --- Параметризованный тест ---
void TestRectangle::contains_parameterized_data() {
    QTest::addColumn<double>("px");
    QTest::addColumn<double>("py");
    QTest::addColumn<bool>("expected");

    QTest::newRow("center") << 5.0 << 5.0 << true;
    QTest::newRow("top_left_corner") << 0.0 << 0.0 << true;
    QTest::newRow("bottom_right_corner") << 10.0 << 10.0 << true;
    QTest::newRow("outside_right") << 10.1 << 5.0 << false;
    QTest::newRow("outside_top") << 5.0 << -0.1 << false;
}

void TestRectangle::contains_parameterized() {
    QFETCH(double, px);
    QFETCH(double, py);
    QFETCH(bool, expected);

    QCOMPARE(mylib::contains({0, 0, 10, 10}, px, py), expected);
}

QTEST_MAIN(TestRectangle)
#include "test_file.moc"