#include "file.h"
#include <QtTest/QtTest>
#include <cmath>

class TestConverter20 : public QObject
{
    Q_OBJECT

private slots:
    // --- Температура: позитивные и негативные ---
    void celsiusToFahrenheit_freezingPoint();
    void celsiusToFahrenheit_boilingPoint();
    void celsiusToKelvin_absoluteZero();
    void celsiusToKelvin_belowAbsoluteZero_returnsMarker();
    void classifyWaterState_data();
    void classifyWaterState();

    // --- Длина: позитивные ---
    void mToKm_basic();
    void mToMiles_basic();
    void mToFeet_basic();
    void mToInches_basic();

    // --- Длина: негативные и граничные ---
    void length_negativeInput_returnsMarker();
    void length_zero_returnsZero();

    // --- Масса: позитивные ---
    void kgToG_basic();
    void kgToTons_basic();
    void kgToPounds_basic();

    // --- Масса: негативные ---
    void mass_negativeInput_returnsMarker();

    // --- Цепочка конвертаций (обратимость) ---
    void roundTrip_length_data();
    void roundTrip_length();
    void roundTrip_mass_data();
    void roundTrip_mass();
    void roundTrip_temperature_celsiusToFahrenheit();
};

// ===== ТЕМПЕРАТУРА =====
void TestConverter20::celsiusToFahrenheit_freezingPoint() {
    QCOMPARE(mylib::celsiusToFahrenheit(0.0), 32.0);
}

void TestConverter20::celsiusToFahrenheit_boilingPoint() {
    QCOMPARE(mylib::celsiusToFahrenheit(100.0), 212.0);
}

void TestConverter20::celsiusToKelvin_absoluteZero() {
    QCOMPARE(mylib::celsiusToKelvin(-273.15), 0.0);
}

void TestConverter20::celsiusToKelvin_belowAbsoluteZero_returnsMarker() {
    QCOMPARE(mylib::celsiusToKelvin(-300.0), -999.0);
}

void TestConverter20::classifyWaterState_data() {
    QTest::addColumn<double>("celsius");
    QTest::addColumn<mylib::WaterState>("expected");

    QTest::newRow("ice_-10")   << -10.0 << mylib::WaterState::Ice;
    QTest::newRow("ice_0")     << 0.0   << mylib::WaterState::Ice;
    QTest::newRow("liquid_25") << 25.0  << mylib::WaterState::Liquid;
    QTest::newRow("liquid_99") << 99.9  << mylib::WaterState::Liquid;
    QTest::newRow("steam_100") << 100.0 << mylib::WaterState::Steam;
    QTest::newRow("steam_150") << 150.0 << mylib::WaterState::Steam;
}

void TestConverter20::classifyWaterState() {
    QFETCH(double, celsius);
    QFETCH(mylib::WaterState, expected);
    QCOMPARE(mylib::classifyWaterState(celsius), expected);
}

// ===== ДЛИНА =====
void TestConverter20::mToKm_basic() {
    QCOMPARE(mylib::mToKm(1000.0), 1.0);
}

void TestConverter20::mToMiles_basic() {
    double r = mylib::mToMiles(1609.344);
    QVERIFY(std::abs(r - 1.0) < 1e-9);
}

void TestConverter20::mToFeet_basic() {
    double r = mylib::mToFeet(0.3048);
    QVERIFY(std::abs(r - 1.0) < 1e-9);
}

void TestConverter20::mToInches_basic() {
    double r = mylib::mToInches(0.0254);
    QVERIFY(std::abs(r - 1.0) < 1e-9);
}

void TestConverter20::length_negativeInput_returnsMarker() {
    QCOMPARE(mylib::mToKm(-5.0), -999.0);
    QCOMPARE(mylib::mToMiles(-1.0), -999.0);
    QCOMPARE(mylib::feetToM(-10.0), -999.0);
}

void TestConverter20::length_zero_returnsZero() {
    QCOMPARE(mylib::mToKm(0.0), 0.0);
    QCOMPARE(mylib::mToMiles(0.0), 0.0);
}

// ===== МАССА =====
void TestConverter20::kgToG_basic() {
    QCOMPARE(mylib::kgToG(1.0), 1000.0);
}

void TestConverter20::kgToTons_basic() {
    QCOMPARE(mylib::kgToTons(1000.0), 1.0);
}

void TestConverter20::kgToPounds_basic() {
    double r = mylib::kgToPounds(0.45359237);
    QVERIFY(std::abs(r - 1.0) < 1e-9);
}

void TestConverter20::mass_negativeInput_returnsMarker() {
    QCOMPARE(mylib::kgToG(-1.0), -999.0);
    QCOMPARE(mylib::tonsToKg(-5.0), -999.0);
}

// ===== ЦЕПОЧКА КОНВЕРТАЦИЙ (ОБРАТИМОСТЬ) =====
void TestConverter20::roundTrip_length_data() {
    QTest::addColumn<double>("value");
    QTest::addColumn<double>("eps");
    QTest::addColumn<QString>("unit");

    QTest::newRow("m_km")    << 1234.5   << 1e-6 << "km";
    QTest::newRow("m_miles") << 5000.0   << 1e-6 << "miles";
    QTest::newRow("m_feet")  << 100.0    << 1e-6 << "feet";
    QTest::newRow("m_inches")<< 3.5      << 1e-6 << "inches";
}

void TestConverter20::roundTrip_length() {
    QFETCH(double, value);
    QFETCH(double, eps);
    QFETCH(QString, unit);

    double back;
    if (unit == "km")     back = mylib::kmToM(mylib::mToKm(value));
    else if (unit == "miles") back = mylib::milesToM(mylib::mToMiles(value));
    else if (unit == "feet")  back = mylib::feetToM(mylib::mToFeet(value));
    else                      back = mylib::inchesToM(mylib::mToInches(value));

    QVERIFY(std::abs(back - value) < eps);
}

void TestConverter20::roundTrip_mass_data() {
    QTest::addColumn<double>("value");
    QTest::addColumn<QString>("unit");

    QTest::newRow("kg_g")      << 2.5   << "g";
    QTest::newRow("kg_tons")   << 1500.0 << "tons";
    QTest::newRow("kg_pounds") << 10.0  << "pounds";
    QTest::newRow("kg_ounces") << 3.0   << "ounces";
}

void TestConverter20::roundTrip_mass() {
    QFETCH(double, value);
    QFETCH(QString, unit);

    double back;
    if (unit == "g")         back = mylib::gToKg(mylib::kgToG(value));
    else if (unit == "tons")   back = mylib::tonsToKg(mylib::kgToTons(value));
    else if (unit == "pounds") back = mylib::poundsToKg(mylib::kgToPounds(value));
    else                       back = mylib::ouncesToKg(mylib::kgToOunces(value));

    QVERIFY(std::abs(back - value) < 1e-6);
}

void TestConverter20::roundTrip_temperature_celsiusToFahrenheit() {
    double c = 25.0;
    double back = mylib::fahrenheitToCelsius(mylib::celsiusToFahrenheit(c));
    QVERIFY(std::abs(back - c) < 1e-9);
}

QTEST_MAIN(TestConverter20)
#include "test_file.moc"