#include <gtest/gtest.h>
#include "matrix.h"
#include <stdexcept>

// 1. НОРМАЛЬНЫЕ СЛУЧАИ

// 1.1. Создание матрицы
TEST(MatrixTest, CreateMatrix_NormalCase) {
    Matrix A = create_matrix(3, 4);
    EXPECT_EQ(A.rows, 3);
    EXPECT_EQ(A.cols, 4);
    EXPECT_NE(A.data, nullptr);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            EXPECT_DOUBLE_EQ(A.data[i][j], 0.0);
        }
    }
    free_matrix(A);
}

// 1.2. Сложение матриц
TEST(MatrixTest, Addition_NormalCase) {
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(2, 2);
    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;
    B.data[0][0] = 5; B.data[0][1] = 6;
    B.data[1][0] = 7; B.data[1][1] = 8;
    Matrix C = matrix_add(A, B);
    EXPECT_DOUBLE_EQ(C.data[0][0], 6.0);
    EXPECT_DOUBLE_EQ(C.data[0][1], 8.0);
    EXPECT_DOUBLE_EQ(C.data[1][0], 10.0);
    EXPECT_DOUBLE_EQ(C.data[1][1], 12.0);
    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
}

// 1.3. Умножение матриц
TEST(MatrixTest, Multiplication_NormalCase) {
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(2, 2);
    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;
    B.data[0][0] = 5; B.data[0][1] = 6;
    B.data[1][0] = 7; B.data[1][1] = 8;
    Matrix C = matrix_multiply(A, B);
    EXPECT_DOUBLE_EQ(C.data[0][0], 19.0);
    EXPECT_DOUBLE_EQ(C.data[0][1], 22.0);
    EXPECT_DOUBLE_EQ(C.data[1][0], 43.0);
    EXPECT_DOUBLE_EQ(C.data[1][1], 50.0);
    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
}

// 1.4. Освобождение памяти - нормальный случай
TEST(MatrixTest, FreeMatrix_NormalCase) {
    Matrix A = create_matrix(3, 3);
    EXPECT_NO_THROW(free_matrix(A));
}

// 2. ГРАНИЧНЫЕ СЛУЧАИ

// 2.1. Минимальный размер матрицы - 1x1
TEST(MatrixTest, CreateMatrix_MinimumSize) {
    Matrix A = create_matrix(1, 1);
    EXPECT_EQ(A.rows, 1);
    EXPECT_EQ(A.cols, 1);
    EXPECT_DOUBLE_EQ(A.data[0][0], 0.0);
    free_matrix(A);
}

// 2.2. Вектор-строка 1x3 умножается на вектор-столбец 3x1, результат 1x1
TEST(MatrixTest, Multiplication_RowTimesColumn_1x1) {
    Matrix A = create_matrix(1, 3);
    Matrix B = create_matrix(3, 1);
    A.data[0][0] = 1; A.data[0][1] = 2; A.data[0][2] = 3;
    B.data[0][0] = 4;
    B.data[1][0] = 5;
    B.data[2][0] = 6;
    Matrix C = matrix_multiply(A, B);
    EXPECT_EQ(C.rows, 1);
    EXPECT_EQ(C.cols, 1);
    EXPECT_DOUBLE_EQ(C.data[0][0], 32.0);
    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
}

// 3. ОШИБОЧНЫЕ СЛУЧАИ

// 3.1. Нулевое число строк
TEST(MatrixTest, CreateMatrix_ZeroRows) {
    EXPECT_THROW(create_matrix(0, 3), std::invalid_argument);
}

// 3.2. Отрицательное число столбцов
TEST(MatrixTest, CreateMatrix_NegativeCols) {
    EXPECT_THROW(create_matrix(3, -1), std::invalid_argument);
}

// 3.3. Сложение матриц разного размера
TEST(MatrixTest, Addition_SizeMismatch) {
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(3, 2);
    EXPECT_THROW(matrix_add(A, B), std::invalid_argument);
    free_matrix(A);
    free_matrix(B);
}

// 3.4. Умножение при несовместимых размерах (cols(A) != rows(B))
TEST(MatrixTest, Multiplication_SizeMismatch) {
    Matrix A = create_matrix(2, 3);
    Matrix B = create_matrix(2, 2);
    EXPECT_THROW(matrix_multiply(A, B), std::invalid_argument);
    free_matrix(A);
    free_matrix(B);
}

// 3.5. Освобождение пустой матрицы (data == nullptr) не падает
TEST(MatrixTest, FreeMatrix_EmptyIsSafe) {
    Matrix empty = {nullptr, 0, 0};
    EXPECT_NO_THROW(free_matrix(empty));
}

// 4. МЕТОД solve_2x2 (ВАРИАНТ 17)

// 4.1. Нормальный случай: 2x + 3y = 8, x + 2y = 5 -> x = 1, y = 2
TEST(MatrixTest, Solve2x2_NormalCase) {
    Matrix A = create_matrix(2, 2);
    A.data[0][0] = 2; A.data[0][1] = 3;
    A.data[1][0] = 1; A.data[1][1] = 2;
    Matrix b = create_matrix(2, 1);
    b.data[0][0] = 8; b.data[1][0] = 5;
    Matrix x = solve_2x2(A, b);
    EXPECT_DOUBLE_EQ(x.data[0][0], 1.0);
    EXPECT_DOUBLE_EQ(x.data[1][0], 2.0);
    free_matrix(A);
    free_matrix(b);
    free_matrix(x);
}

// 4.2. Вырожденная система (определитель 0) - исключение
TEST(MatrixTest, Solve2x2_ZeroDeterminant) {
    Matrix A = create_matrix(2, 2);
    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 2; A.data[1][1] = 4;
    Matrix b = create_matrix(2, 1);
    b.data[0][0] = 1; b.data[1][0] = 1;
    EXPECT_THROW(solve_2x2(A, b), std::runtime_error);
    free_matrix(A);
    free_matrix(b);
}

// 4.3. Неверный размер матрицы A - исключение
TEST(MatrixTest, Solve2x2_WrongSize) {
    Matrix A = create_matrix(3, 3);
    Matrix b = create_matrix(2, 1);
    EXPECT_THROW(solve_2x2(A, b), std::invalid_argument);
    free_matrix(A);
    free_matrix(b);
}