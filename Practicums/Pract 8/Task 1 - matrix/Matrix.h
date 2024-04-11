#pragma once
#include <iostream>

class Matrix
{
	double** data = nullptr;
	size_t rows = 0;
	size_t cols = 0;
	bool isSameDimensionalAs(const Matrix& mat) const;
	bool canBeMultipliedWith(const Matrix& mat) const;
	bool isSquare() const;
	void copyFrom(const Matrix& other);
	void free();
public:
	Matrix();
	Matrix(size_t rows, size_t cols);
	Matrix(double** data, size_t rows, size_t cols);
	Matrix(const Matrix& other);
	~Matrix();
	Matrix& operator=(const Matrix& other);

	Matrix& operator+=(const Matrix& rhs);
	Matrix& operator-=(const Matrix& rhs);
	Matrix& operator*=(const Matrix& rhs);
	Matrix& operator*=(double num);
	Matrix& operator/=(double num);

	const double* operator[](int index) const;
	double* operator[](int index);

	Matrix& operator++();
	Matrix operator++(int a);

	friend Matrix operator~(const Matrix& mat);

	friend bool operator==(const Matrix& lhs, const Matrix& rhs);
	friend bool operator!=(const Matrix& lhs, const Matrix& rhs);
	friend bool operator!(const Matrix& matrix);

	friend std::ostream& operator<<(std::ostream& os, const Matrix& mat);
	friend std::istream& operator>>(std::istream& is, Matrix& mat);

	bool isSymmetric() const;
};
Matrix operator+(const Matrix& lhs, const Matrix& rhs);
Matrix operator-(const Matrix& lhs, const Matrix& rhs);
Matrix operator*(const Matrix& lhs, const Matrix& rhs);
Matrix operator*(const Matrix& lhs, double num);
Matrix operator*(double num, const Matrix& mat);
Matrix operator/(const Matrix& lhs, double num);