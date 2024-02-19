#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>
#include <omp.h>

using namespace std::chrono;

const int SIZE = 400;
int matrixA[SIZE][SIZE];
int matrixB[SIZE][SIZE];
int resultMatrix[SIZE][SIZE];

void generateRandomMatrix(int matrix[][SIZE]) {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            matrix[i][j] = rand() % 100;
        }
    }
}

int main() {
    srand(time(0));
    generateRandomMatrix(matrixA);
    generateRandomMatrix(matrixB);

    auto startTime = high_resolution_clock::now();
    
    #pragma omp parallel for collapse(3)
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < SIZE; ++k) {
                resultMatrix[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }

    auto stopTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stopTime - startTime);
    
    printf("Execution time: %d microseconds\n", duration.count());

    std::ofstream outputFile("OpenMP_Results.txt");
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
