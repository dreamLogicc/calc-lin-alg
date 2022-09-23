#include <iostream>
#include <time.h>
#include <math.h>
#include <fstream>

int **createMatrix(int size)
{
    int **matrix = new int *[size];
    for (int i = 0; i < size; i++)
        matrix[i] = new int[size];

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            matrix[i][j] = 1 + rand() % 100;
    return matrix;
}

// Function fills matrix with zeros
void initZero(int **matr, int size)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            matr[i][j] = 0;
}

void mult(int **A, int **B, int **C, int n, int blockCount)
{
    int sblock = n / blockCount;
    for (int kb = 0; kb < blockCount; kb++)
        for (int ib = 0; ib < blockCount; ib++)
            for (int jb = 0; jb < blockCount; jb++)
                for (int k = 0; k < sblock; k++)
                    for (int i = 0; i < sblock; i++)
                        for (int j = 0; j < sblock; j++)
                            C[ib * sblock + i][jb * sblock + j] += A[ib * sblock + i][kb * sblock + k] * B[kb * sblock + k][jb * sblock + j];
}

unsigned int timeOf(void (*multiply)(int **, int **, int **, int, int), int **A, int **B, int **C, int size, int block)
{
    unsigned int start = clock();
    multiply(A, B, C, size, block);
    unsigned int end = clock();
    unsigned int time = end - start;
    return time;
}

void clear(int **matrix, int size)
{
    for (int i = 0; i < size; i++)
        delete[] matrix[i];
    delete[] matrix;
}

int main()
{
    srand(time(0));
    std::ofstream outputCsv;
    outputCsv.open("result.csv");

    int sizes[4] = {512, 1024, 1536, 2048};
    int blockCount[10];

    for (int i = 1; i <= 10; i++)
        blockCount[i] = pow(2, i);

    outputCsv << "Blocks" << ',';

    for (int i = 0; i < 4; i++)
        outputCsv << sizes[i] << ',';
        
    outputCsv << std::endl;

    for (int j = 1; j <= 10; j++)
    {
        outputCsv << blockCount[j] << ',';
        for (int k = 0; k < 4; k++)
        {
            if ((sizes[k] - blockCount[j] >= 0) && (sizes[k] % blockCount[j] == 0))
            {
                int **A = createMatrix(sizes[k]); // Creating matrix A with random numbers
                int **B = createMatrix(sizes[k]); // Creating matrix B with random numbers
                int **C = createMatrix(sizes[k]); // Creating matrix C with random numbers
                initZero(C, sizes[k]);
                outputCsv << (double)timeOf(mult, A, B, C, sizes[k], blockCount[j]) / 1000 << ',';
                clear(A, sizes[k]);
                clear(B, sizes[k]);
                clear(C, sizes[k]);
            }
            else
                outputCsv << 0 << ',';
        }
        outputCsv << std::endl;
    }
    outputCsv.close();
}
