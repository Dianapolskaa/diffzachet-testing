#include "file.h"

namespace mylib {

double celsiusToFahrenheit(double celsius) {
    return celsius * 9.0 / 5.0 + 32.0;
}

double celsiusToKelvin(double celsius) {
    if (celsius < -273.15) {
        return -999.0; // Ниже абсолютного нуля
    }
    return celsius + 273.15;
}

double fahrenheitToCelsius(double fahrenheit) {
    return (fahrenheit - 32.0) * 5.0 / 9.0;
}

double kelvinToCelsius(double kelvin) {
    if (kelvin < 0.0) {
        return -999.0; // Отрицательный Кельвин невозможен
    }
    return kelvin - 273.15;
}

WaterState classifyWaterState(double celsius) {
    if (celsius <= 0.0) {
        return WaterState::Ice;
    }
    if (celsius < 100.0) {
        return WaterState::Liquid;
    }
    return WaterState::Steam;
}

} // namespace mylib