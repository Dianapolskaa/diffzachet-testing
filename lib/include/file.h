#pragma once
#include <string>
#include <vector>
#include <stdexcept>

namespace mylib {

// Структура для записи в историю операций
struct Transaction {
    std::string type; // "DEPOSIT", "WITHDRAW", "INTEREST"
    double amount;
};

class BankAccount {
public:
    // Конструктор. Бросает std::invalid_argument, если initialBalance < 0 или interestRate < 0.
    explicit BankAccount(double initialBalance = 0.0, double interestRate = 0.0);

    double getBalance() const;
    double getInterestRate() const;

    // Изменение процентной ставки. Бросает std::invalid_argument, если rate < 0.
    void setInterestRate(double rate);

    // Пополнение счёта. Бросает std::invalid_argument, если amount <= 0.
    void deposit(double amount);

    // Снятие со счёта.
    // Бросает std::invalid_argument, если amount <= 0.
    // Бросает std::runtime_error, если amount > balance (недостаточно средств).
    void withdraw(double amount);

    // Начисление процентов за заданное количество периодов.
    // Формула: balance += balance * interestRate * periods.
    // Бросает std::invalid_argument, если periods <= 0.
    // Если начисленные проценты > 0, они добавляются в баланс и историю.
    void applyInterest(int periods);

    // Проверка достаточности средств.
    bool hasSufficientFunds(double amount) const;

    // Возвращает константную ссылку на историю операций.
    const std::vector<Transaction>& getHistory() const;

private:
    double balance_;
    double interestRate_;
    std::vector<Transaction> history_;
};

} // namespace mylib