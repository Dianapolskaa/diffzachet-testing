#pragma once

namespace mylib {

enum class WaterState {
    Ice,        // Лёд (<= 0°C, точка замерзания)
    Liquid,     // Жидкость (0°C < t < 100°C)
    Steam       // Пар (>= 100°C, точка кипения)
};

// ===== ТЕМПЕРАТУРА =====
// Ошибочные ситуации: значения ниже абсолютного нуля (-273.15°C / 0K)
// возвращают маркер -999.0.
double celsiusToFahrenheit(double celsius);
double celsiusToKelvin(double celsius);
double fahrenheitToCelsius(double fahrenheit);
double kelvinToCelsius(double kelvin);
WaterState classifyWaterState(double celsius);

// ===== ДЛИНА (базовая единица — метр) =====
// Ошибочные ситуации: отрицательные значения возвращают маркер -999.0.
double mToKm(double m);
double kmToM(double km);
double mToMiles(double m);
double milesToM(double miles);
double mToFeet(double m);
double feetToM(double feet);
double mToInches(double m);
double inchesToM(double inches);

// ===== МАССА (базовая единица — килограмм) =====
// Ошибочные ситуации: отрицательные значения возвращают маркер -999.0.
double kgToG(double kg);
double gToKg(double g);
double kgToTons(double kg);
double tonsToKg(double tons);
double kgToPounds(double kg);
double poundsToKg(double pounds);
double kgToOunces(double kg);
double ouncesToKg(double ounces);

} // namespace mylib