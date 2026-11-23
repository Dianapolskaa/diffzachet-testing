#pragma once
#include <stdexcept>

namespace mylib {

// Прогрессивная шкала налога (НДФЛ):
// 0 - 50 000: 13%
// 50 001 - 100 000: 15%
// > 100 000: 20%
//
// Обработка ошибок:
// Бросает std::invalid_argument, если grossSalary < 0.
double calculateProgressiveTax(double grossSalary);

// Бонус по KPI (Key Performance Indicator):
// KPI < 50: бонус 0%
// 50 <= KPI < 80: бонус 10% от оклада
// KPI >= 80: бонус 20% от оклада
//
// Обработка ошибок:
// Бросает std::invalid_argument, если baseSalary < 0 или kpi < 0.
double calculateKpiBonus(double baseSalary, double kpi);

// Итоговая зарплата на руки (Net Salary):
// Gross = baseSalary + calculateKpiBonus(baseSalary, kpi)
// Net = Gross - calculateProgressiveTax(Gross)
//
// Обработка ошибок:
// Бросает std::invalid_argument при некорректных входных данных.
double calculateNetSalary(double baseSalary, double kpi);

} // namespace mylib