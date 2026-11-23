#pragma once
#include <vector>
#include <stdexcept>

namespace mylib {

using Matrix = std::vector<std::vector<double>>;

// Создание нулевой матрицы размера rows x cols.
// Бросает std::invalid_argument, если rows <= 0 или cols <= 0.
Matrix createMatrix(int rows, int cols);

// Создание единичной матрицы размера n x n.
// Бросает std::invalid_argument, если n <= 0.
Matrix identityMatrix(int n);

// Сложение матриц.
// Бросает std::invalid_argument, если размеры не совпадают.
Matrix add(const Matrix& a, const Matrix& b);

// Умножение матриц.
// Бросает std::invalid_argument, если количество столбцов a не равно количеству строк b.
Matrix multiply(const Matrix& a, const Matrix& b);

// Транспонирование матрицы.
Matrix transpose(const Matrix& m);

// Вычисление определителя квадратной матрицы.
// Бросает std::invalid_argument, если матрица не квадратная.
double determinant(const Matrix& m);

// Получение размера матрицы.
int rows(const Matrix& m);
int cols(const Matrix& m);

} // namespace mylib