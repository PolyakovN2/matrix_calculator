/**
 * @file matrix.h
 * @brief Библиотека для работы с матрицами.
 * @author Студент
 * @version 0.1
 */
#ifndef MATRIX_H
#define MATRIX_H

/**
 * @brief Структура матрицы.
 *
 * Хранит двумерный динамический массив и его размеры.
 * @warning Память освобождается через free_matrix().
 */
typedef struct {
    double** data; ///< Указатель на двумерный массив.
    int rows;      ///< Количество строк.
    int cols;      ///< Количество столбцов.
} Matrix;

/**
 * @brief Создание матрицы заданного размера.
 *
 * @param rows Количество строк (> 0).
 * @param cols Количество столбцов (> 0).
 * @return Matrix Инициализированная нулями матрица.
 * @exception std::invalid_argument Если rows <= 0 или cols <= 0.
 * @exception std::bad_alloc Если не удалось выделить память.
 * @see free_matrix()
 */
Matrix create_matrix(int rows, int cols);

/**
 * @brief Освобождение памяти матрицы.
 *
 * @param m Матрица, память которой нужно освободить.
 * @warning Структура m передаётся по значению, поэтому поля исходной матрицы
 * не обнуляются. После вызова не обращайтесь к исходной матрице.
 */
void free_matrix(Matrix m);

/**
 * @brief Сложение двух матриц одинакового размера.
 *
 * @param a Первая матрица.
 * @param b Вторая матрица того же размера.
 * @return Matrix Новая матрица-сумма.
 * @exception std::invalid_argument Если размеры не совпадают.
 */
Matrix matrix_add(Matrix a, Matrix b);

/**
 * @brief Умножение двух матриц.
 *
 * @param a Матрица размером M×N.
 * @param b Матрица размером N×K.
 * @return Matrix Результат размером M×K.
 * @exception std::invalid_argument Если a.cols != b.rows.
 * @note Время выполнения: O(M*N*K).
 * @warning Результат нужно освободить через free_matrix().
 */
Matrix matrix_multiply(Matrix a, Matrix b);

/**
 * @brief Вывод матрицы в консоль.
 *
 * Для матриц больше 10×8 выводится сокращённый вид.
 *
 * @param m Матрица для вывода.
 */
void print_matrix(Matrix m);

/**
 * @brief Создание матрицы из одномерного массива.
 *
 * Элементы заполняют матрицу построчно.
 *
 * @param data Одномерный массив из rows * cols элементов.
 * @param rows Количество строк.
 * @param cols Количество столбцов.
 * @return Matrix Новая матрица.
 * @exception std::invalid_argument Если data == nullptr.
 */
Matrix matrix_from_array(double* data, int rows, int cols);

/**
 * @brief Решение системы двух линейных уравнений A·x = b методом Крамера.
 *
 * @param A Матрица коэффициентов размером 2×2.
 * @param b Вектор правых частей размером 2×1.
 * @return Matrix Вектор решения x размером 2×1.
 * @exception std::invalid_argument Если A не 2×2 или b не 2×1.
 * @exception std::runtime_error Если определитель A равен нулю.
 */
Matrix solve_2x2(Matrix A, Matrix b);

#endif