#include "file.h"
#include <QtTest/QtTest>
#include <cmath>

class TestTemperature : public QObject
{
    Q_OBJECT

private slots:
    // Позитивные: конвертация Цельсий → Фаренгейт
    void celsiusToFahrenheit_freezingPoint();
    void celsiusToFahrenheit_boilingPoint();
    void celsiusToFahrenheit_zero();

    // Позитивные: конвертация Цельсий → Кельвин
    void celsiusToKelvin_freezingPoint();
    void celsiusToKelvin_boilingPoint();
    void celsiusToKelvin_absoluteZero();

    // Негативные: ниже абсолютного нуля
    void celsiusToKelvin_belowAbsoluteZero();

    // Позитивные: обратная конвертация
    void fahrenheitToCelsius_freezingPoint();
    void fahrenheitToCelsius_boilingPoint();
    void kelvinToCelsius_freezingPoint();
    void kelvinToCelsius_absoluteZero();

    // Негативные: отрицательный Кельвин
    void kelvinToCelsius_negativeKelvin();

    // Классификация состояния воды (параметризованный тест)
    void classifyWaterState_data();
    void classifyWaterState();

    // Граничные случаи
    void celsiusToFahrenheit_negativeTemperature();
    void roundTrip_celsiusToFahrenheitToCelsius();
};

// --- Цельсий → Фаренгейт ---
void TestTemperature::celsiusToFahrenheit_freezingPoint() {
    QCOMPARE(mylib::celsiusToFahrenheit(0.0), 32.0);
}

void TestTemperature::celsiusToFahrenheit_boilingPoint() {
    QCOMPARE(mylib::celsiusToFahrenheit(100.0), 212.0);
}

void TestTemperature::celsiusToFahrenheit_zero() {
    QCOMPARE(mylib::celsiusToFahrenheit(0.0), 32.0);
}

// --- Цельсий → Кельвин ---
void TestTemperature::celsiusToKelvin_freezingPoint() {
    QCOMPARE(mylib::celsiusToKelvin(0.0), 273.15);
}

void TestTemperature::celsiusToKelvin_boilingPoint() {
    QCOMPARE(mylib::celsiusToKelvin(100.0), 373.15);
}

void TestTemperature::celsiusToKelvin_absoluteZero() {
    QCOMPARE(mylib::celsiusToKelvin(-273.15), 0.0);
}

void TestTemperature::celsiusToKelvin_belowAbsoluteZero() {
    QCOMPARE(mylib::celsiusToKelvin(-300.0), -999.0);
}

// --- Фаренгейт → Цельсий ---
void TestTemperature::fahrenheitToCelsius_freezingPoint() {
    QCOMPARE(mylib::fahrenheitToCelsius(32.0), 0.0);
}

void TestTemperature::fahrenheitToCelsius_boilingPoint() {
    QCOMPARE(mylib::fahrenheitToCelsius(212.0), 100.0);
}

// --- Кельвин → Цельсий ---
void TestTemperature::kelvinToCelsius_freezingPoint() {
    QCOMPARE(mylib::kelvinToCelsius(273.15), 0.0);
}

void TestTemperature::kelvinToCelsius_absoluteZero() {
    QCOMPARE(mylib::kelvinToCelsius(0.0), -273.15);
}

void TestTemperature::kelvinToCelsius_negativeKelvin() {
    QCOMPARE(mylib::kelvinToCelsius(-10.0), -999.0);
}

// --- Классификация состояния воды (параметризованный тест) ---
void TestTemperature::classifyWaterState_data() {
    QTest::addColumn<double>("celsius");
    QTest::addColumn<mylib::WaterState>("expected");
    QTest::addColumn<QString>("description");

    QTest::newRow("ice_negative") << -10.0 << mylib::WaterState::Ice << "Лёд при -10°C";
    QTest::newRow("ice_atZero") << 0.0 << mylib::WaterState::Ice << "Лёд при 0°C (граница)";
    QTest::newRow("liquid_roomTemp") << 25.0 << mylib::WaterState::Liquid << "Жидкость при 25°C";
    QTest::newRow("liquid_atBoiling") << 99.9 << mylib::WaterState::Liquid << "Жидкость при 99.9°C";
    QTest::newRow("steam_atBoiling") << 100.0 << mylib::WaterState::Steam << "Пар при 100°C (граница)";
    QTest::newRow("steam_high") << 150.0 << mylib::WaterState::Steam << "Пар при 150°C";
}

void TestTemperature::classifyWaterState() {
    QFETCH(double, celsius);
    QFETCH(mylib::WaterState, expected);
    QFETCH(QString, description);

    QCOMPARE(mylib::classifyWaterState(celsius), expected);
}

// --- Граничные случаи ---
void TestTemperature::celsiusToFahrenheit_negativeTemperature() {
    QCOMPARE(mylib::celsiusToFahrenheit(-40.0), -40.0); // -40°C = -40°F
}

void TestTemperature::roundTrip_celsiusToFahrenheitToCelsius() {
    double original = 25.0;
    double fahrenheit = mylib::celsiusToFahrenheit(original);
    double backToCelsius = mylib::fahrenheitToCelsius(fahrenheit);
    QVERIFY(std::abs(backToCelsius - original) < 1e-9);
}

QTEST_MAIN(TestTemperature)
#include "test_file.moc"