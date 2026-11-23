#pragma once

namespace mylib {

enum class WaterState {
    Ice,        // Лёд (ниже 0°C)
    Liquid,     // Жидкость (0°C до 100°C)
    Steam       // Пар (выше 100°C)
};

// Перевод Цельсий → Фаренгейт
// Формула: F = C * 9/5 + 32
double celsiusToFahrenheit(double celsius);

// Перевод Цельсий → Кельвин
// Формула: K = C + 273.15
// Если celsius < -273.15 (ниже абсолютного нуля), возвращает -999.0
double celsiusToKelvin(double celsius);

// Перевод Фаренгейт → Цельсий
// Формула: C = (F - 32) * 5/9
double fahrenheitToCelsius(double fahrenheit);

// Перевод Кельвин → Цельсий
// Формула: C = K - 273.15
// Если kelvin < 0, возвращает -999.0
double kelvinToCelsius(double kelvin);

// Классификация состояния воды по температуре в Цельсиях.
// Граничные условия задокументированы: 0°C считается льдом (точка замерзания),
// 100°C — паром (точка кипения).
WaterState classifyWaterState(double celsius);

} // namespace mylib