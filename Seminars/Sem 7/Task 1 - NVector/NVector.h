#pragma once
#include <iostream>

class NVector
{
	double* data = nullptr;
	size_t size = 0;
	void copyFrom(const NVector& other);
	void free();
public:
	NVector() = default;
	NVector(size_t size);
	NVector(const NVector& other);
	~NVector();
	NVector& operator=(const NVector& other);

	NVector& operator+=(const NVector& vector);
	NVector& operator-=(const NVector& vector);
	NVector& operator*=(double scalar);

	size_t getLength() const;

	double& operator[](int index);
	double operator[](int index) const;

	friend std::ostream& operator<<(std::ostream& os, const NVector& vector);
	friend std::istream& operator>>(std::istream& is, NVector& vector);
};
//are parallel
bool operator||(const NVector& first, const NVector& second);
//are perpendicular
bool operator|=(const NVector& first, const NVector& second);

NVector operator+(const NVector& first, const NVector& second);
NVector operator-(const NVector& first, const NVector& second);
double operator%(const NVector& first, const NVector& second);

NVector operator*(const NVector& vector, double scalar);
NVector operator*(double scalar, const NVector& vector);