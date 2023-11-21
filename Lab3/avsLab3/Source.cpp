#include <iostream>
#include <chrono>
#include <omp.h>

// Функция для умножения матриц на матрицу (без параллельных вычислений)
void multiplyMatricesSequential(int** A, int** B, int** C, int rowsA, int colsA, int colsB) {
    for (int i = 0; i < rowsA; ++i)
        for (int j = 0; j < colsB; ++j)
            for (int k = 0; k < colsA; ++k)
                C[i][j] += A[i][k] * B[k][j];
}

// Функция для умножения матриц на матрицу (с параллельными вычислениями)
void multiplyMatrices(int** A, int** B, int** C, int rowsA, int colsA, int colsB) {
#pragma omp parallel for collapse(3)
    for (int i = 0; i < rowsA; ++i)
        for (int j = 0; j < colsB; ++j)
            for (int k = 0; k < colsA; ++k)
                C[i][j] += A[i][k] * B[k][j];
}

int main() {
    // Задаем размеры матриц
    constexpr int rowsA = 1000, colsA = 1000, rowsB = 1000, colsB = 1000;

    if constexpr (rowsA != colsB)
    {
        std::cout << "A rows and B columns must be equals" << std::endl;
        return 0;
    }

    // Инициализация матриц A, B и C

    // Выделение памяти и заполнение матриц A и B (ваш код)
    int** A = new int* [rowsA];
    for (int i = 0; i < rowsA; ++i) {
        A[i] = new int[colsA];
        for (int j = 0; j < colsA; ++j) {
            A[i][j] = 1; // Пример инициализации, замените данными вашего кода
        }
    }

    int** B = new int* [rowsB];
    for (int i = 0; i < rowsB; ++i) {
        B[i] = new int[colsB];
        for (int j = 0; j < colsB; ++j) {
            B[i][j] = 2; // Пример инициализации, замените данными вашего кода
        }
    }

    // Выделение памяти для матрицы C
    int** C = new int* [rowsA];
    for (int i = 0; i < rowsA; ++i) {
        C[i] = new int[colsB];

        for (int j = 0; j < colsB; ++j)
            C[i][j] = 0;
    }

    // Засекаем время выполнения для последовательного умножения матриц
    auto startSequential = std::chrono::high_resolution_clock::now();
    multiplyMatricesSequential(A, B, C, rowsA, colsA, colsB);
    auto endSequential = std::chrono::high_resolution_clock::now();
    double sequentialTime = std::chrono::duration<double, std::milli>(endSequential - startSequential).count();

    // Засекаем время выполнения для параллельного умножения матриц
    auto startParallel = std::chrono::high_resolution_clock::now();
    multiplyMatrices(A, B, C, rowsA, colsA, colsB);
    auto endParallel = std::chrono::high_resolution_clock::now();
    double parallelTime = std::chrono::duration<double, std::milli>(endParallel - startParallel).count();

    // Вывод времени выполнения
    std::cout << "Sequential Time: " << sequentialTime / 1000 << " milliseconds" << std::endl;
    std::cout << "Parallel Time: " << parallelTime / 1000 << " milliseconds" << std::endl;

    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}