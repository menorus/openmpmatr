#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <omp.h>

const int SIZE = 1000; // ������ ������

// ������� ��� ���������� ������� ���������� �������
void fillMatrix(std::vector<std::vector<int>>& matrix) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            matrix[i][j] = rand() % 100; // ��������� ����� �� 0 �� 99
        }
    }
}

// ������� ��� ������������ ������ � �������������� OpenMP
void multiplyMatrices(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C) {
#pragma omp parallel for num_threads(omp_get_max_threads())
    for (int i = 0; i < SIZE; ++i) {
//#pragma omp parallel for num_threads(omp_get_max_threads())
        for (int j = 0; j < SIZE; ++j) {
            int sum = 0;
//#pragma omp parallel for num_threads(omp_get_max_threads())
            for (int k = 0; k < SIZE; ++k) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
}
void multiplyMatrices11(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C) {
//#pragma omp parallel for num_threads(omp_get_max_threads())
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            int sum = 0;
            for (int k = 0; k < SIZE; ++k) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
}
int main() {
    // ������������� ���������� ��������� �����
    srand(static_cast<unsigned>(time(0)));

    // �������� ������
    std::vector<std::vector<int>> A(SIZE, std::vector<int>(SIZE));
    std::vector<std::vector<int>> B(SIZE, std::vector<int>(SIZE));
    std::vector<std::vector<int>> C(SIZE, std::vector<int>(SIZE, 0));

    // ���������� ������ A � B ���������� �������
    fillMatrix(A);
    fillMatrix(B);

    // ��������� ������� ����������
    double start = omp_get_wtime();
    multiplyMatrices(A, B, C);
    double end = omp_get_wtime();

    // ����� ������� ����������
    std::cout << "Time taken for matrix multiplication: " << (end - start) << " seconds" << std::endl;
    double start1 = omp_get_wtime();
    multiplyMatrices11(A, B, C);
    double end1 = omp_get_wtime();

    // ����� ������� ����������
    std::cout << "Time taken for matrix multiplication: " << (end1 - start1) << " seconds" << std::endl;
    return 0;
}
