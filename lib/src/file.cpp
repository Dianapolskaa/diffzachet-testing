#include "file.h"

namespace mylib {

double calculateProgressiveTax(double grossSalary) {
    if (grossSalary < 0.0) {
        throw std::invalid_argument("Gross salary cannot be negative");
    }

    double tax = 0.0;
    if (grossSalary <= 50000.0) {
        tax = grossSalary * 0.13;
    } else if (grossSalary <= 100000.0) {
        tax = 50000.0 * 0.13 + (grossSalary - 50000.0) * 0.15;
    } else {
        tax = 50000.0 * 0.13 + 50000.0 * 0.15 + (grossSalary - 100000.0) * 0.20;
    }
    return tax;
}

double calculateKpiBonus(double baseSalary, double kpi) {
    if (baseSalary < 0.0 || kpi < 0.0) {
        throw std::invalid_argument("Base salary and KPI cannot be negative");
    }

    if (kpi < 50.0) return 0.0;
    if (kpi < 80.0) return baseSalary * 0.10;
    return baseSalary * 0.20;
}

double calculateNetSalary(double baseSalary, double kpi) {
    if (baseSalary < 0.0 || kpi < 0.0) {
        throw std::invalid_argument("Base salary and KPI cannot be negative");
    }

    double gross = baseSalary + calculateKpiBonus(baseSalary, kpi);
    double tax = calculateProgressiveTax(gross);
    return gross - tax;
}

} // namespace mylib