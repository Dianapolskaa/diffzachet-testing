#pragma once
#include <string>
#include <vector>
#include <stdexcept>

namespace mylib {

// Элемент корзины: название товара, цена за единицу, количество.
struct CartItem {
    std::string name;
    double price;      // Цена за единицу (должна быть >= 0)
    int quantity;      // Количество (должно быть >= 0)
};

// Вычисляет сумму корзины без скидок и НДС.
// Формула: sum(price_i * quantity_i), результат округляется до копеек.
// Бросает std::invalid_argument, если цена < 0 или количество < 0.
double calculateTotal(const std::vector<CartItem>& cart);

// Применяет процентную скидку, если сумма >= порога.
// Если сумма < threshold, возвращается исходная сумма.
// Результат округляется до копеек.
// Бросает std::invalid_argument, если percent < 0 или percent > 100, threshold < 0.
double applyDiscount(double total, double threshold, double percent);

// Вычисляет сумму с учётом НДС.
// Формула: total * (1 + vatRate/100), результат округляется до копеек.
// Бросает std::invalid_argument, если vatRate < 0.
double calculateWithVAT(double total, double vatRate);

// Применяет акцию "3 по цене 2" к каждому элементу корзины.
// За каждые 3 единицы товара оплачиваются только 2.
// Возвращает новую сумму с учётом акции, округлённую до копеек.
// Бросает std::invalid_argument при некорректных данных.
double applyBuy3Pay2(const std::vector<CartItem>& cart);

// Комплексный расчёт: сумма + акция "3 по цене 2" + скидка + НДС.
// Порядок: сначала акция, потом скидка (если порог достигнут), потом НДС.
double calculateFinal(const std::vector<CartItem>& cart,
                      double discountThreshold, double discountPercent,
                      double vatRate);

} // namespace mylib