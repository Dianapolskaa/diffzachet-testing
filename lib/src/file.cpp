#include "file.h"
#include <cmath>
#include <climits>

namespace mylib {

long long gcd(long long a, long long b) {
    a = std::abs(a);
    b = std::abs(b);
    while (b != 0) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

long long lcm(long long a, long long b) {
    if (a == 0 || b == 0) {
        return 0;
    }
    a = std::abs(a);
    b = std::abs(b);

    long long g = gcd(a, b);
    long long div = a / g;

    // Проверка переполнения перед умножением
    if (div > LLONG_MAX / b) {
        throw std::overflow_error("LCM result overflows long long");
    }

    return div * b;
}

std::vector<long long> primeFactors(long long n) {
    std::vector<long long> factors;
    n = std::abs(n);

    if (n <= 1) {
        return factors; // Пустой вектор для 0, 1 и -1
    }

    for (long long i = 2; i * i <= n; ++i) {
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    }

    if (n > 1) {
        factors.push_back(n);
    }

    return factors;
}

} // namespace mylib