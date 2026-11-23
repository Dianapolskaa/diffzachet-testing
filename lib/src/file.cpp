#include "file.h"
#include <cmath>

namespace mylib {

Matrix createMatrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Matrix dimensions must be positive");
    }
    return Matrix(rows, std::vector<double>(cols, 0.0));
}

Matrix identityMatrix(int n) {
    if (n <= 0) {
        throw std::invalid_argument("Matrix dimension must be positive");
    }
    Matrix result(n, std::vector<double>(n, 0.0));
    for (int i = 0; i < n; ++i) {
        result[i][i] = 1.0;
    }
    return result;
}

Matrix add(const Matrix& a, const Matrix& b) {
    if (rows(a) != rows(b) || cols(a) != cols(b)) {
        throw std::invalid_argument("Matrix dimensions must match for addition");
    }

    int r = rows(a);
    int c = cols(a);
    Matrix result(r, std::vector<double>(c));

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
    return result;
}

Matrix multiply(const Matrix& a, const Matrix& b) {
    if (cols(a) != rows(b)) {
        throw std::invalid_argument("Matrix dimensions incompatible for multiplication");
    }

    int r = rows(a);
    int c = cols(b);
    int k = cols(a);
    Matrix result(r, std::vector<double>(c, 0.0));

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            for (int p = 0; p < k; ++p) {
                result[i][j] += a[i][p] * b[p][j];
            }
        }
    }
    return result;
}

Matrix transpose(const Matrix& m) {
    int r = rows(m);
    int c = cols(m);
    Matrix result(c, std::vector<double>(r));

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            result[j][i] = m[i][j];
        }
    }
    return result;
}

double determinant(const Matrix& m) {
    int n = rows(m);
    if (n != cols(m)) {
        throw std::invalid_argument("Determinant requires square matrix");
    }

    // Базовые случаи
    if (n == 1) {
        return m[0][0];
    }
    if (n == 2) {
        return m[0][0] * m[1][1] - m[0][1] * m[1][0];
    }

    // Рекурсивное вычисление через разложение по первой строке
    double det = 0.0;
    for (int j = 0; j < n; ++j) {
        // Создаём минор (матрица без строки 0 и столбца j)
        Matrix minor(n - 1, std::vector<double>(n - 1));
        for (int i = 1; i < n; ++i) {
            int col = 0;
            for (int k = 0; k < n; ++k) {
                if (k != j) {
                    minor[i - 1][col] = m[i][k];
                    col++;
                }
            }
        }

        double sign = (j % 2 == 0) ? 1.0 : -1.0;
        det += sign * m[0][j] * determinant(minor);
    }

    return det;
}

int rows(const Matrix& m) {
    return m.size();
}

int cols(const Matrix& m) {
    return m.empty() ? 0 : m[0].size();
}

} // namespace mylib