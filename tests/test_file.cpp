#include "file.h"
#include <QtTest/QtTest>
#include <cmath>

class TestTriangle24 : public QObject
{
    Q_OBJECT

private slots:
    // 1. Проверка существования (негативные и граничные)
    void exists_zeroSide_false();
    void exists_negativeSide_false();
    void exists_degenerateTriangle_false(); // a + b = c
    
    // 2. Вид по сторонам (акцент на варианты из методички)
    void typeBySides_equilateral();
    void typeBySides_isosceles_firstTwo();  // 5, 5, 3
    void typeBySides_isosceles_lastTwo();   // 3, 5, 5
    void typeBySides_scalene();
    
    // 3. Вид по углам (параметризованный тест + египетский треугольник)
    void typeByAngles_data();
    void typeByAngles();
    
    // 4. Ключевое требование варианта 24: порядок сторон не влияет
    void orderIndependence_typeByAngles();
    void orderIndependence_area();
    
    // 5. Площадь по Герону
    void area_egyptianTriangle();
    void area_invalidTriangle_negative();
};

// --- 1. Существование ---
void TestTriangle24::exists_zeroSide_false() {
    QVERIFY(!mylib::exists(0, 5, 5));
    QVERIFY(!mylib::exists(5, 0, 5));
}

void TestTriangle24::exists_negativeSide_false() {
    QVERIFY(!mylib::exists(-3, 4, 5));
}

void TestTriangle24::exists_degenerateTriangle_false() {
    // Вырожденный треугольник (сумма двух равна третьей)
    QVERIFY(!mylib::exists(1, 2, 3));
    QVERIFY(!mylib::exists(2, 3, 5));
}

// --- 2. Вид по сторонам ---
void TestTriangle24::typeBySides_equilateral() {
    QCOMPARE(mylib::typeBySides(5, 5, 5), mylib::TriangleType::Equilateral);
}

void TestTriangle24::typeBySides_isosceles_firstTwo() {
    QCOMPARE(mylib::typeBySides(5, 5, 3), mylib::TriangleType::Isosceles);
}

void TestTriangle24::typeBySides_isosceles_lastTwo() {
    QCOMPARE(mylib::typeBySides(3, 5, 5), mylib::TriangleType::Isosceles);
}

void TestTriangle24::typeBySides_scalene() {
    QCOMPARE(mylib::typeBySides(3, 4, 5), mylib::TriangleType::Scalene);
}

// --- 3. Вид по углам ---
void TestTriangle24::typeByAngles_data() {
    QTest::addColumn<double>("a");
    QTest::addColumn<double>("b");
    QTest::addColumn<double>("c");
    QTest::addColumn<mylib::AngleType>("expected");
    QTest::addColumn<QString>("description");

    // Египетский треугольник (прямоугольный)
    QTest::newRow("egyptian_3_4_5") << 3.0 << 4.0 << 5.0 << mylib::AngleType::Right << "Египетский";
    QTest::newRow("egyptian_5_12_13") << 5.0 << 12.0 << 13.0 << mylib::AngleType::Right << "Египетский большой";
    // Остроугольный
    QTest::newRow("acute_5_5_5") << 5.0 << 5.0 << 5.0 << mylib::AngleType::Acute << "Равносторонний";
    // Тупоугольный
    QTest::newRow("obtuse_2_3_4") << 2.0 << 3.0 << 4.0 << mylib::AngleType::Obtuse << "Тупоугольный";
}

void TestTriangle24::typeByAngles() {
    QFETCH(double, a);
    QFETCH(double, b);
    QFETCH(double, c);
    QFETCH(mylib::AngleType, expected);
    QFETCH(QString, description);

    QCOMPARE(mylib::typeByAngles(a, b, c), expected);
}

// --- 4. Независимость от порядка сторон (Требование варианта 24) ---
void TestTriangle24::orderIndependence_typeByAngles() {
    // Египетский треугольник в разных порядках должен давать Right
    QCOMPARE(mylib::typeByAngles(3, 4, 5), mylib::AngleType::Right);
    QCOMPARE(mylib::typeByAngles(4, 5, 3), mylib::AngleType::Right);
    QCOMPARE(mylib::typeByAngles(5, 3, 4), mylib::AngleType::Right);
}

void TestTriangle24::orderIndependence_area() {
    double area1 = mylib::area(3, 4, 5);
    double area2 = mylib::area(5, 3, 4);
    double area3 = mylib::area(4, 5, 3);
    
    QVERIFY(std::abs(area1 - area2) < 1e-9);
    QVERIFY(std::abs(area2 - area3) < 1e-9);
    QVERIFY(std::abs(area1 - 6.0) < 1e-9); // Площадь 3-4-5 = 6
}

// --- 5. Площадь ---
void TestTriangle24::area_egyptianTriangle() {
    QCOMPARE(mylib::area(3, 4, 5), 6.0);
}

void TestTriangle24::area_invalidTriangle_negative() {
    QCOMPARE(mylib::area(1, 2, 10), -1.0);
}

QTEST_MAIN(TestTriangle24)
#include "test_file.moc"
