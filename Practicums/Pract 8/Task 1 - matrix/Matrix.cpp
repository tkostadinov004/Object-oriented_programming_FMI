#include "Matrix.h"

bool Matrix::isSameDimensionalAs(const Matrix& mat) const
{
	return this->rows == mat.rows && this->cols == mat.cols;
}

bool Matrix::canBeMultipliedWith(const Matrix& mat) const
{
	return this->cols == mat.rows;
}

bool Matrix::isSquare() const
{
	return rows == cols;
}

void Matrix::copyFrom(const Matrix& other)
{
	this->data = new double* [other.rows];
	for (size_t i = 0; i < other.rows; i++)
	{
		this->data[i] = new double[other.cols];
		for (size_t j = 0; j < other.cols; j++)
		{
			this->data[i][j] = other.data[i][j];
		}
	}
	this->rows = other.rows;
	this->cols = other.cols;
}

void Matrix::free()
{
	for (size_t i = 0; i < rows; i++)
	{
		delete[] data[i];
	}
	delete[] data;
}

Matrix::Matrix() : Matrix(2, 2)
{
}

Matrix::Matrix(size_t rows, size_t cols) : Matrix(nullptr, rows, cols)
{
}

Matrix::Matrix(double** data, size_t rows, size_t cols)
{
	this->data = new double* [rows];
	for (size_t i = 0; i < rows; i++)
	{
		this->data[i] = new double[cols] {0};
		if (data && data[i])
		{
			for (size_t j = 0; j < cols; j++)
			{
				this->data[i][j] = data[i][j];
			}
		}
	}
	this->rows = rows;
	this->cols = cols;
}

Matrix::Matrix(const Matrix& other)
{
	copyFrom(other);
}

Matrix::~Matrix()
{
	free();
}

Matrix& Matrix::operator=(const Matrix& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Matrix& Matrix::operator+=(const Matrix& rhs)
{
	if (isSameDimensionalAs(rhs))
	{
		for (size_t i = 0; i < rows; i++)
		{
			for (size_t j = 0; j < cols; j++)
			{
				this->data[i][j] += rhs.data[i][j];
			}
		}
	}
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& rhs)
{
	if (isSameDimensionalAs(rhs))
	{
		for (size_t i = 0; i < rows; i++)
		{
			for (size_t j = 0; j < cols; j++)
			{
				this->data[i][j] -= rhs.data[i][j];
			}
		}
	}
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& rhs)
{
	if (!canBeMultipliedWith(rhs))
	{
		return *this;
	}

	Matrix result(this->rows, rhs.cols);
	for (size_t i = 0; i < this->rows; i++)
	{
		for (size_t j = 0; j < rhs.cols; j++)
		{
			double mult_result = 0;
			for (size_t k = 0; k < cols; k++)
			{
				mult_result += (this->data[i][k] * rhs.data[k][i]);
			}
			result[i][j] = mult_result;
		}
	}
	*this = result;
	return result;
}

Matrix& Matrix::operator*=(double num)
{
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			this->data[i][j] *= num;
		}
	}
	return *this;
}

Matrix& Matrix::operator/=(double num)
{
	if (num == 0)
	{
		return *this;
	}

	return *this *= (1 / num);
}

Matrix operator~(const Matrix& mat)
{
	Matrix transposed(mat.cols, mat.rows);
	for (size_t i = 0; i < mat.cols; i++)
	{
		for (size_t j = 0; j < mat.rows; j++)
		{
			transposed[i][j] = mat.data[j][i];
		}
	}
	return transposed;
}

const double* Matrix::operator[](int index) const
{
	if (index < 0 || index >= rows)
	{
		return nullptr;
	}
	return data[index];
}

double* Matrix::operator[](int index)
{
	if (index < 0 || index >= rows)
	{
		return nullptr;
	}
	return data[index];
}

Matrix& Matrix::operator++()
{
	if (isSquare())
	{
		for (size_t i = 0; i < rows; i++)
		{
			this->data[i][i]++;
		}
	}
	return *this;
}

Matrix Matrix::operator++(int a)
{
	Matrix result(*this);
	++*this;
	return result;
}

bool Matrix::isSymmetric() const
{
	if (!isSquare())
	{
		return false;
	}

	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			if (data[i][j] != data[j][i])
			{
				return false;
			}
		}
	}
	return true;
}

bool operator==(const Matrix& lhs, const Matrix& rhs)
{
	if (!lhs.isSameDimensionalAs(rhs))
	{
		return false;
	}


	for (size_t i = 0; i < lhs.rows; i++)
	{
		for (size_t j = 0; j < lhs.cols; j++)
		{
			if (lhs.data[i][j] != rhs.data[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

bool operator!=(const Matrix& lhs, const Matrix& rhs)
{
	return !(lhs == rhs);
}

bool operator!(const Matrix& matrix)
{
	for (size_t i = 0; i < matrix.rows; i++)
	{
		for (size_t j = 0; j < matrix.cols; j++)
		{
			if (matrix.data[i][j] != 0)
			{
				return false;
			}
		}
	}
	return true;
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs)
{
	Matrix result(lhs);
	result += rhs;
	return result;
}

Matrix operator-(const Matrix& lhs, const Matrix& rhs)
{
	Matrix result(lhs);
	result -= rhs;
	return result;
}

Matrix operator*(const Matrix& lhs, const Matrix& rhs)
{
	Matrix result(lhs);
	result *= rhs;
	return result;
}

Matrix operator*(const Matrix& lhs, double num)
{
	Matrix result(lhs);
	result *= num;
	return result;
}

Matrix operator*(double num, const Matrix& mat)
{
	return mat * num;
}

Matrix operator/(const Matrix& lhs, double num)
{
	if (num == 0)
	{
		return Matrix();
	}
	return lhs * (1 / num);
}

std::ostream& operator<<(std::ostream& os, const Matrix& mat)
{
	os << mat.rows << " " << mat.cols << std::endl;
	for (size_t i = 0; i < mat.rows; i++)
	{
		for (size_t j = 0; j < mat.cols; j++)
		{
			os << mat.data[i][j];
			if (j < mat.cols - 1)
			{
				os << " ";
			}
		}
		os << std::endl;
	}
	return os;
}

std::istream& operator>>(std::istream& is, Matrix& mat)
{
	is >> mat.rows >> mat.cols;
	mat.free();
	mat.data = new double* [mat.rows];
	for (size_t i = 0; i < mat.rows; i++)
	{
		mat.data[i] = new double[mat.cols];
		for (size_t j = 0; j < mat.cols; j++)
		{
			is >> mat.data[i][j];
		}
	}
	return is;
}
