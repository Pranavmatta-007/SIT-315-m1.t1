#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>
#include <pthread.h>

using namespace std::chrono;

const int SIZE = 200;
#define MAX_THREADS 16

int matrixA[SIZE][SIZE];
int matrixB[SIZE][SIZE];
int resultMatrix[SIZE][SIZE];
int threadCounter = 0;
int partitionSize = SIZE / MAX_THREADS;

void generateRandomMatrix(int matrix[][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            matrix[i][j] = rand() % 100;
        }
    }
}

void* performMatrixMultiplication(void* args) {
    int threadID = threadCounter++;
    for (int i = threadID * partitionSize; i < (threadID + 1) * partitionSize; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            resultMatrix[i][j] = 0;
            for (int k = 0; k < SIZE; ++k) {
                resultMatrix[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    return NULL;
}

int main() {
    srand(time(0));
    generateRandomMatrix(matrixA);
    generateRandomMatrix(matrixB);

    auto startTime = high_resolution_clock::now();
    
    pthread_t matrixThreads[MAX_THREADS];
    for (int i = 0; i < MAX_THREADS; ++i) {
        pthread_create(&matrixThreads[i], NULL, &performMatrixMultiplication, NULL);
    }

    for (int i = 0; i < MAX_THREADS; ++i) {
        pthread_join(matrixThreads[i], NULL);
    }

    auto stopTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stopTime - startTime);

    printf("Execution time: %d microseconds", duration.count());

    std::ofstream outputFile("PThread_matrix.txt");
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
