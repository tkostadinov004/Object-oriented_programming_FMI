#include <iostream>
#include "Matrix.h"

void freeMemory(double** matrix, size_t rows)
{
	if (!matrix)
	{
		return;
	}
	for (size_t i = 0; i < rows; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}
int main()
{
	double** m1Data = new double* [3] {new double[3] {2, 3, 4}, new double[3] {1, 2, 3}, new double[3] {0, 1, 0}};
	Matrix m1(m1Data, 3, 3);
	double** m2Data = new double* [3] {new double[4] {0, 1, 1, 0}, new double[4] {2, 3, 4, 1}, new double[4] {1, 1, 1, 0}};
	Matrix m2(m2Data, 3, 4);

	freeMemory(m1Data, 3);
	freeMemory(m2Data, 3);
	std::cout << m1 * m2 << std::endl;

	std::cout << m1 << std::endl;
	std::cout << ~m1 << std::endl;

	std::cout << m2 << std::endl;
	std::cout << ~m2 << std::endl;

	m1 += m2;
	std::cout << m1 << std::endl;

	std::cout << !m1 << std::endl;
	std::cout << !(m1 * 0) << std::endl;

	std::cout << std::endl << m1 << std::endl;
	std::cout << m1++ << std::endl;
	std::cout << ++m1 << std::endl;
}