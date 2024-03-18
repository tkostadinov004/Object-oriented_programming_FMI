#include <iostream>
#include <fstream>

struct Matrix
{
	int** data;
	size_t rows;
	size_t cols;

	Matrix()
	{
		data = nullptr;
		rows = 0;
		cols = 0;
	}
	Matrix(size_t rows, size_t cols)
	{
		this->rows = rows;
		this->cols = cols;

		data = new int* [rows];
	}
	Matrix(const Matrix& matrix)
	{
		rows = matrix.rows;
		cols = matrix.cols;
		data = new int* [rows];
		for (size_t i = 0; i < matrix.rows; i++)
		{
			data[i] = new int[matrix.cols];
			for (size_t j = 0; j < matrix.cols; j++)
			{
				this->data[i][j] = matrix.data[i][j];
			}
		}
	}
	~Matrix()
	{
		for (size_t i = 0; i < this->rows; i++)
		{
			delete[] data[i];
		}
		delete[] data;
	}
	Matrix multiplyBy(const Matrix& other) const
	{
		if (this->cols != other.rows)
		{
			return {};
		}

		Matrix result(this->rows, other.cols);

		for (size_t i = 0; i < this->rows; i++)
		{
			result.data[i] = new int[other.cols] {0};
			for (size_t j = 0; j < other.cols; j++)
			{
				for (size_t k = 0; k < other.rows; k++)
				{
					result.data[i][j] += (this->data[i][k] * other.data[k][j]);
				}
			}
		}
		return result;
	}
};
void serializeMatrix(std::ofstream& ofs, const Matrix& matrix)
{
	ofs.write((const char*)&matrix.rows, sizeof(matrix.rows));
	ofs.write((const char*)&matrix.cols, sizeof(matrix.cols));
	for (size_t i = 0; i < matrix.rows; i++)
	{
		ofs.write((const char*)matrix.data[i], matrix.cols * sizeof(int));
	}
}
void serializeMatrix(const char* filename, const Matrix& matrix)
{
	if (!filename)
	{
		return;
	}

	std::ofstream ofs(filename, std::ios::binary);
	if (!ofs.is_open())
	{
		return;
	}

	serializeMatrix(ofs, matrix);
}
void deserializeMatrix(std::ifstream& ifs, Matrix& matrix)
{
	ifs.read((char*)&matrix.rows, sizeof(matrix.rows));
	ifs.read((char*)&matrix.cols, sizeof(matrix.cols));

	matrix.data = new int* [matrix.rows];
	for (size_t i = 0; i < matrix.rows; i++)
	{
		matrix.data[i] = new int[matrix.cols];
		ifs.read((char*)matrix.data[i], matrix.cols * sizeof(int));
	}
}
void deserializeMatrix(const char* filename, Matrix& matrix)
{
	if (!filename)
	{
		return;
	}

	std::ifstream ifs(filename, std::ios::binary);
	if (!ifs.is_open())
	{
		return;
	}

	deserializeMatrix(ifs, matrix);
}
int main()
{
	/*Matrix first(2, 3);
	first.data[0] = new int[3]{ 1,2,3 };
	first.data[1] = new int[3]{ 4,5,6 };
	serializeMatrix("first.dat", first);
	Matrix second(3, 2);
	second.data[0] = new int[2] { 10, 11 };
	second.data[1] = new int[2] { 20, 21 };
	second.data[2] = new int[2] { 30, 31 };
	serializeMatrix("second.dat", second);*/

	Matrix first, second;
	deserializeMatrix("first.dat", first);
	deserializeMatrix("second.dat", second);

	Matrix mult = first.multiplyBy(second);
	if (!mult.data)
	{
		std::cout << "Unable to multiply matrices!";
		return -1;
	}

	serializeMatrix("result.dat", mult);
}