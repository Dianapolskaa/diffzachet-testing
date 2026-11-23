#include "file.h"
#include <cmath>

namespace mylib {

// Округление до копеек (2 знака после запятой)
static double roundToCents(double value) {
    return std::round(value * 100.0) / 100.0;
}

double calculateTotal(const std::vector<CartItem>& cart) {
    double sum = 0.0;
    for (const auto& item : cart) {
        if (item.price < 0.0) {
            throw std::invalid_argument("Negative price for item: " + item.name);
        }
        if (item.quantity < 0) {
            throw std::invalid_argument("Negative quantity for item: " + item.name);
        }
        sum += item.price * item.quantity;
    }
    return roundToCents(sum);
}

double applyDiscount(double total, double threshold, double percent) {
    if (total < 0.0) {
        throw std::invalid_argument("Total cannot be negative");
    }
    if (threshold < 0.0) {
        throw std::invalid_argument("Threshold cannot be negative");
    }
    if (percent < 0.0 || percent > 100.0) {
        throw std::invalid_argument("Discount percent must be in [0, 100]");
    }
    if (total < threshold) {
        return total; // Скидка не применяется
    }
    double discounted = total * (1.0 - percent / 100.0);
    return roundToCents(discounted);
}

double calculateWithVAT(double total, double vatRate) {
    if (total < 0.0) {
        throw std::invalid_argument("Total cannot be negative");
    }
    if (vatRate < 0.0) {
        throw std::invalid_argument("VAT rate cannot be negative");
    }
    double withVat = total * (1.0 + vatRate / 100.0);
    return roundToCents(withVat);
}

double applyBuy3Pay2(const std::vector<CartItem>& cart) {
    double sum = 0.0;
    for (const auto& item : cart) {
        if (item.price < 0.0) {
            throw std::invalid_argument("Negative price for item: " + item.name);
        }
        if (item.quantity < 0) {
            throw std::invalid_argument("Negative quantity for item: " + item.name);
        }
        // За каждые 3 штуки платим за 2.
        // Оплачиваемых единиц = quantity - quantity / 3
        int paidQuantity = item.quantity - item.quantity / 3;
        sum += item.price * paidQuantity;
    }
    return roundToCents(sum);
}

double calculateFinal(const std::vector<CartItem>& cart,
                      double discountThreshold, double discountPercent,
                      double vatRate) {
    // 1. Сначала акция "3 по цене 2"
    double afterPromo = applyBuy3Pay2(cart);
    // 2. Потом скидка (если порог достигнут)
    double afterDiscount = applyDiscount(afterPromo, discountThreshold, discountPercent);
    // 3. Потом НДС
    return calculateWithVAT(afterDiscount, vatRate);
}

} // namespace mylib