#include "file.h"
#include <QtTest/QtTest>
#include <cmath>

class TestTriangle : public QObject
{
    Q_OBJECT

private slots:
    // Позитивные: существование
    void exists_validTriangle_true();
    void exists_positiveSides_true();
    
    // Негативные: несуществующие треугольники
    void exists_negativeSide_false();
    void exists_zeroSide_false();
    void exists_inequalityViolation_false();
    void exists_degenerateTriangle_false();
    
    // Тип по сторонам
    void typeBySides_equilateral();
    void typeBySides_isosceles();
    void typeBySides_scalene();
    void typeBySides_invalidTriangle();
    
    // Тип по углам - параметризованный тест
    void typeByAngles_data();
    void typeByAngles();
    
    // Площадь
    void area_validTriangle_positive();
    void area_equilateralTriangle();
    void area_invalidTriangle_negative();
    
    // Периметр
    void perimeter_validTriangle_sum();
    void perimeter_invalidTriangle_negative();
    
    // Граничные случаи
    void exists_veryLargeNumbers_true();
    void area_verySmallNumbers_positive();
};

void TestTriangle::exists_validTriangle_true()
{
    QVERIFY(mylib::exists(3, 4, 5));
}

void TestTriangle::exists_positiveSides_true()
{
    QVERIFY(mylib::exists(1, 1, 1));
}

void TestTriangle::exists_negativeSide_false()
{
    QVERIFY(!mylib::exists(-1, 2, 3));
    QVERIFY(!mylib::exists(1, -2, 3));
    QVERIFY(!mylib::exists(1, 2, -3));
}

void TestTriangle::exists_zeroSide_false()
{
    QVERIFY(!mylib::exists(0, 2, 3));
    QVERIFY(!mylib::exists(1, 0, 3));
    QVERIFY(!mylib::exists(1, 2, 0));
}

void TestTriangle::exists_inequalityViolation_false()
{
    QVERIFY(!mylib::exists(1, 2, 10));
    QVERIFY(!mylib::exists(10, 1, 2));
}

void TestTriangle::exists_degenerateTriangle_false()
{
    // Вырожденный: a + b = c
    QVERIFY(!mylib::exists(1, 2, 3));
    QVERIFY(!mylib::exists(2, 3, 5));
}

void TestTriangle::typeBySides_equilateral()
{
    QCOMPARE(mylib::typeBySides(5, 5, 5), mylib::TriangleType::Equilateral);
}

void TestTriangle::typeBySides_isosceles()
{
    QCOMPARE(mylib::typeBySides(5, 5, 3), mylib::TriangleType::Isosceles);
    QCOMPARE(mylib::typeBySides(3, 5, 5), mylib::TriangleType::Isosceles);
    QCOMPARE(mylib::typeBySides(5, 3, 5), mylib::TriangleType::Isosceles);
}

void TestTriangle::typeBySides_scalene()
{
    QCOMPARE(mylib::typeBySides(3, 4, 5), mylib::TriangleType::Scalene);
}

void TestTriangle::typeBySides_invalidTriangle()
{
    QCOMPARE(mylib::typeBySides(1, 2, 10), mylib::TriangleType::Invalid);
}

void TestTriangle::typeByAngles_data()
{
    QTest::addColumn<double>("a");
    QTest::addColumn<double>("b");
    QTest::addColumn<double>("c");
    QTest::addColumn<mylib::AngleType>("expected");
    
    QTest::newRow("right_3_4_5") << 3.0 << 4.0 << 5.0 << mylib::AngleType::Right;
    QTest::newRow("acute_5_5_5") << 5.0 << 5.0 << 5.0 << mylib::AngleType::Acute;
    QTest::newRow("obtuse_2_3_4") << 2.0 << 3.0 << 4.0 << mylib::AngleType::Obtuse;
    QTest::newRow("right_5_12_13") << 5.0 << 12.0 << 13.0 << mylib::AngleType::Right;
}

void TestTriangle::typeByAngles()
{
    QFETCH(double, a);
    QFETCH(double, b);
    QFETCH(double, c);
    QFETCH(mylib::AngleType, expected);
    
    QCOMPARE(mylib::typeByAngles(a, b, c), expected);
}

void TestTriangle::area_validTriangle_positive()
{
    double a = mylib::area(3, 4, 5);
    QVERIFY(a > 0);
    QVERIFY(std::abs(a - 6.0) < 1e-9); // Площадь прямоугольного 3-4-5 = 6
}

void TestTriangle::area_equilateralTriangle()
{
    double a = mylib::area(2, 2, 2);
    double expected = std::sqrt(3.0); // sqrt(3) для равностороннего со стороной 2
    QVERIFY(std::abs(a - expected) < 1e-9);
}

void TestTriangle::area_invalidTriangle_negative()
{
    QCOMPARE(mylib::area(1, 2, 10), -1.0);
}

void TestTriangle::perimeter_validTriangle_sum()
{
    QCOMPARE(mylib::perimeter(3, 4, 5), 12.0);
}

void TestTriangle::perimeter_invalidTriangle_negative()
{
    QCOMPARE(mylib::perimeter(1, 2, 10), -1.0);
}

void TestTriangle::exists_veryLargeNumbers_true()
{
    QVERIFY(mylib::exists(1e10, 1e10, 1e10));
}

void TestTriangle::area_verySmallNumbers_positive()
{
    double a = mylib::area(0.001, 0.001, 0.001);
    QVERIFY(a > 0);
}

QTEST_MAIN(TestTriangle)
#include "test_file.moc"
