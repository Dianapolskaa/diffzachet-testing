#include "file.h"

namespace mylib {

BankAccount::BankAccount(double initialBalance, double interestRate)
    : balance_(initialBalance), interestRate_(interestRate) {
    if (initialBalance < 0.0) {
        throw std::invalid_argument("Initial balance cannot be negative");
    }
    if (interestRate < 0.0) {
        throw std::invalid_argument("Interest rate cannot be negative");
    }
}

double BankAccount::getBalance() const { return balance_; }
double BankAccount::getInterestRate() const { return interestRate_; }

void BankAccount::setInterestRate(double rate) {
    if (rate < 0.0) {
        throw std::invalid_argument("Interest rate cannot be negative");
    }
    interestRate_ = rate;
}

void BankAccount::deposit(double amount) {
    if (amount <= 0.0) {
        throw std::invalid_argument("Deposit amount must be positive");
    }
    balance_ += amount;
    history_.push_back({"DEPOSIT", amount});
}

void BankAccount::withdraw(double amount) {
    if (amount <= 0.0) {
        throw std::invalid_argument("Withdraw amount must be positive");
    }
    if (amount > balance_) {
        throw std::runtime_error("Insufficient funds");
    }
    balance_ -= amount;
    history_.push_back({"WITHDRAW", amount});
}

void BankAccount::applyInterest(int periods) {
    if (periods <= 0) {
        throw std::invalid_argument("Periods must be positive");
    }
    double interest = balance_ * interestRate_ * periods;
    // Начисляем и добавляем в историю только если есть реальный доход
    if (interest > 0.0) {
        balance_ += interest;
        history_.push_back({"INTEREST", interest});
    }
}

const std::vector<Transaction>& BankAccount::getHistory() const {
    return history_;
}

bool BankAccount::hasSufficientFunds(double amount) const {
    return balance_ >= amount;
}

} // namespace mylib