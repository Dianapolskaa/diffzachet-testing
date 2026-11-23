#include "file.h"

namespace mylib {

// ===== ТЕМПЕРАТУРА =====
double celsiusToFahrenheit(double celsius) {
    return celsius * 9.0 / 5.0 + 32.0;
}

double celsiusToKelvin(double celsius) {
    if (celsius < -273.15) return -999.0;
    return celsius + 273.15;
}

double fahrenheitToCelsius(double fahrenheit) {
    return (fahrenheit - 32.0) * 5.0 / 9.0;
}

double kelvinToCelsius(double kelvin) {
    if (kelvin < 0.0) return -999.0;
    return kelvin - 273.15;
}

WaterState classifyWaterState(double celsius) {
    if (celsius <= 0.0) return WaterState::Ice;
    if (celsius < 100.0) return WaterState::Liquid;
    return WaterState::Steam;
}

// ===== ДЛИНА =====
double mToKm(double m)    { return m < 0.0 ? -999.0 : m / 1000.0; }
double kmToM(double km)   { return km < 0.0 ? -999.0 : km * 1000.0; }
double mToMiles(double m) { return m < 0.0 ? -999.0 : m / 1609.344; }
double milesToM(double mi){ return mi < 0.0 ? -999.0 : mi * 1609.344; }
double mToFeet(double m)  { return m < 0.0 ? -999.0 : m / 0.3048; }
double feetToM(double ft) { return ft < 0.0 ? -999.0 : ft * 0.3048; }
double mToInches(double m){ return m < 0.0 ? -999.0 : m / 0.0254; }
double inchesToM(double in){ return in < 0.0 ? -999.0 : in * 0.0254; }

// ===== МАССА =====
double kgToG(double kg)     { return kg < 0.0 ? -999.0 : kg * 1000.0; }
double gToKg(double g)      { return g < 0.0 ? -999.0 : g / 1000.0; }
double kgToTons(double kg)  { return kg < 0.0 ? -999.0 : kg / 1000.0; }
double tonsToKg(double t)   { return t < 0.0 ? -999.0 : t * 1000.0; }
double kgToPounds(double kg){ return kg < 0.0 ? -999.0 : kg / 0.45359237; }
double poundsToKg(double lb){ return lb < 0.0 ? -999.0 : lb * 0.45359237; }
double kgToOunces(double kg){ return kg < 0.0 ? -999.0 : kg / 0.028349523125; }
double ouncesToKg(double oz){ return oz < 0.0 ? -999.0 : oz * 0.028349523125; }

} // namespace mylib