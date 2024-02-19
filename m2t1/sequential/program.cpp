#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>

using namespace std::chrono;

const int SIZE = 400;

void generateRandomMatrix(int matrix[][SIZE]) {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            matrix[i][j] = rand() % 100;
}

void performMatrixMultiplication(const int matrix1[][SIZE], const int matrix2[][SIZE], int resultMatrix[][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            resultMatrix[i][j] = 0;
            for (int k = 0; k < SIZE; ++k) {
                resultMatrix[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

int main() {
    srand(time(nullptr));
    int matrix1[SIZE][SIZE];
    int matrix2[SIZE][SIZE];
    int resultMatrix[SIZE][SIZE];

    generateRandomMatrix(matrix1);
    generateRandomMatrix(matrix2);

    auto startTime = high_resolution_clock::now();
    performMatrixMultiplication(matrix1, matrix2, resultMatrix);
    auto stopTime = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stopTime - startTime);
    std::cout << "Multiplication completed in: " << duration.count() << " microseconds" << std::endl;

    std::ofstream outputFile("Result_matrix.txt");
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            outputFile << resultMatrix[i][j] << "\t";
        }
        outputFile << std::endl;
    }
    outputFile << "Execution time: " << duration.count() << " microseconds";
    outputFile.close();

    return 0;
}
