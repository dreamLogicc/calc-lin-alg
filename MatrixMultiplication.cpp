#include <iostream>
#include <time.h>

// Function generates matrix with random numbers
int** createMatrix(int size) {
	int** matrix = new int*[size];
	for (int i = 0; i < size; i++)
	{
		matrix[i] = new int[size];
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			matrix[i][j] = 1 + rand() % 100;
		}
		
	}
	return matrix;
}

// Function fills matrix with zeros
void initZero(int** matr, int size){
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			matr[i][j] = 0;
		}
		
	}
	
}

// Matrix multiplication function. Cycle sequence: i-j-k
void multiplyMatrix_ijk(int** A, int** B, int** C, int size) {
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			for (int k = 0; k < size; k++)
			{
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
}

// Matrix multiplication function. Cycle sequence: i-k-j
void multiplyMatrix_ikj(int** A, int** B, int** C, int size){
	for (int i = 0; i < size; i++)
	{
		for (int k = 0; k < size; k++)
		{
			for (int j = 0; j < size; j++)
			{
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
}

// Matrix multiplication function. Cycle sequence: j-i-k
void multiplyMatrix_jik(int** A, int** B, int** C, int size){
	for (int j = 0; j < size; j++)
	{
		for (int i = 0; i < size; i++)
		{
			for (int k = 0; k < size; k++)
			{
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
}

// Matrix multiplication function. Cycle sequence: j-k-i
void multiplyMatrix_jki(int** A, int** B, int** C, int size){
	for (int j = 0; j < size; j++)
	{
		for (int k = 0; k < size; k++)
		{
			for (int i = 0; i < size; i++)
			{
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
}

// Matrix multiplication function. Cycle sequence: k-i-j
void multiplyMatrix_kij(int** A, int** B, int** C, int size){
	for (int k = 0; k < size; k++)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
}

// Matrix multiplication function. Cycle sequence: k-j-i
void multiplyMatrix_kji(int** A, int** B, int** C, int size){
	for (int k = 0; k < size; k++)
	{
		for (int j = 0; j < size; j++)
		{
			for (int i = 0; i < size; i++)
			{
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
}

// Matrix multiplication time measurement function
unsigned int timeOf(void (*multiply)(int **, int**, int**, int), int** A, int** B,int ** C, int size) {
	unsigned int start = clock();
	multiply(A, B, C, size);
	std::cout << std::endl;
	unsigned int end = clock();
	unsigned int time = end - start;
	return time;
}

int main()
{
	int size;
	std::cout << "Input matrix size: ";
	std::cin >> size;

	int** A = createMatrix(size); // Creating matrix A with random numbers
	int** B = createMatrix(size); // Creating matrix B with random numbers
	int** C = createMatrix(size); // Creating matrix C with random numbers
	initZero(C, size); // Fill matrix C with zeros

	unsigned int times[6] = {0}; // Array for the execution times of algorithms

	times[0] = timeOf(multiplyMatrix_ijk, A, B, C, size);
	initZero(C, size);
	times[1] = timeOf(multiplyMatrix_ikj, A, B, C, size);
	initZero(C, size);
	times[2] = timeOf(multiplyMatrix_jik, A, B, C, size);
	initZero(C, size);
	times[3] = timeOf(multiplyMatrix_jki, A, B, C, size);
	initZero(C, size);
	times[4] = timeOf(multiplyMatrix_kij, A, B, C, size);
	initZero(C, size);
	times[5] = timeOf(multiplyMatrix_kji, A, B, C, size);
	initZero(C, size);

	for (int i = 0; i < 6; i++)
	{
		std::cout << (double)times[i]/1000 << std::endl;
	}
	
	// Clear memory
	for (int i = 0; i < size; i++)
	{
		delete[] A[i];
		delete[] B[i];
		delete[] C[i];
	}
	delete[] A, B, C;

	system("pause");
}