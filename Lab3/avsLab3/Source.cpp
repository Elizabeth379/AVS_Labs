#include <iostream>
#include <chrono>
#include <omp.h>

// ������� ��� ��������� ������ �� ������� (��� ������������ ����������)
void multiplyMatricesSequential(int** A, int** B, int** C, int rowsA, int colsA, int colsB) {
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < colsA; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// ������� ��� ��������� ������ �� ������� (� ������������� ������������)
void multiplyMatrices(int** A, int** B, int** C, int rowsA, int colsA, int colsB) {
#pragma omp parallel for
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < colsA; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    // ������ ������� ������
    int rowsA = 1000, colsA = 1000, rowsB = 1000, colsB = 1000;

    if (rowsA != colsB)
    {
        std::cout << "A rows and B columns must be equals" << std::endl;
        return 0;
    }

    // ������������� ������ A, B � C
    int** A, ** B, ** C;

    // ��������� ������ � ���������� ������ A � B (��� ���)
    A = new int* [rowsA];
    for (int i = 0; i < rowsA; ++i) {
        A[i] = new int[colsA];
        for (int j = 0; j < colsA; ++j) {
            A[i][j] = 1; // ������ �������������, �������� ������� ������ ����
        }
    }

    B = new int* [rowsB];
    for (int i = 0; i < rowsB; ++i) {
        B[i] = new int[colsB];
        for (int j = 0; j < colsB; ++j) {
            B[i][j] = 2; // ������ �������������, �������� ������� ������ ����
        }
    }

    // ��������� ������ ��� ������� C
    C = new int* [rowsA];
    for (int i = 0; i < rowsA; ++i) {
        C[i] = new int[colsB];
    }

    //    // ����� ������ A � B
    //    std::cout << "Matrix A:" << std::endl;
    //    for (int i = 0; i < rowsA; ++i) {
    //        for (int j = 0; j < colsA; ++j) {
    //            std::cout << A[i][j] << " ";
    //        }
    //        std::cout << std::endl;
    //    }
    //
    //    std::cout << "Matrix B:" << std::endl;
    //    for (int i = 0; i < rowsB; ++i) {
    //        for (int j = 0; j < colsB; ++j) {
    //            std::cout << B[i][j] << " ";
    //        }
    //        std::cout << std::endl;
    //    }

        // �������� ����� ���������� ��� ����������������� ��������� ������
    auto startSequential = std::chrono::high_resolution_clock::now();
    multiplyMatricesSequential(A, B, C, rowsA, colsA, colsB);
    auto endSequential = std::chrono::high_resolution_clock::now();
    double sequentialTime = std::chrono::duration<double, std::milli>(endSequential - startSequential).count();

    // ����� �������������� ������� C
//    std::cout << "Result matrix C (Sequential):" << std::endl;
//    for (int i = 0; i < rowsA; ++i) {
//        for (int j = 0; j < colsB; ++j) {
//            std::cout << C[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }
//
    // �������� ����� ���������� ��� ������������� ��������� ������
    auto startParallel = std::chrono::high_resolution_clock::now();
    multiplyMatrices(A, B, C, rowsA, colsA, colsB);
    auto endParallel = std::chrono::high_resolution_clock::now();
    double parallelTime = std::chrono::duration<double, std::milli>(endParallel - startParallel).count();

    //    // ����� �������������� ������� C
    //    std::cout << "Result matrix C (Parallel):" << std::endl;
    //    for (int i = 0; i < rowsA; ++i) {
    //        for (int j = 0; j < colsB; ++j) {
    //            std::cout << C[i][j] << " ";
    //        }
    //        std::cout << std::endl;
    //    }

        // ����� ������� ����������
    std::cout << "Sequential Time: " << sequentialTime / 1000 << " milliseconds" << std::endl;
    std::cout << "Parallel Time: " << parallelTime / 1000 << " milliseconds" << std::endl;

    return 0;
}
