#include "NVector.h"

void NVector::copyFrom(const NVector& other)
{
	this->data = new double[other.size];
	for (size_t i = 0; i < other.size; i++)
	{
		this->data[i] = other.data[i];
	}
	this->size = other.size;
}

void NVector::free()
{
	delete[] data;
	data = nullptr;
	size = 0;
}

NVector::NVector(size_t size)
{
	this->data = new double[size] {0};
	this->size = size;
}

NVector::NVector(const NVector& other)
{
	copyFrom(other);
}

NVector::~NVector()
{
	free();
}

NVector& NVector::operator=(const NVector& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

NVector& NVector::operator+=(const NVector& vector)
{
	if (this->size != vector.size)
	{
		throw "The dimensions of the two vectors are not equal!";
	}

	for (size_t i = 0; i < vector.size; i++)
	{
		this->data[i] += vector.data[i];
	}
	return *this;
}

NVector& NVector::operator-=(const NVector& vector)
{
	if (this->size != vector.size)
	{
		throw "The dimensions of the two vectors are not equal!";
	}

	for (size_t i = 0; i < vector.size; i++)
	{
		this->data[i] -= vector.data[i];
	}
	return *this;
}

NVector& NVector::operator*=(double scalar)
{
	for (size_t i = 0; i < this->size; i++)
	{
		this->data[i] *= scalar;
	}
	return *this;
}

size_t NVector::getLength() const
{
	return size;
}

double& NVector::operator[](int index)
{
	if (index < 0 || index >= size)
	{
		throw "Index is outside of the vector's bounds";
	}
	return data[index];
}

double NVector::operator[](int index) const
{
	if (index < 0 || index >= size)
	{
		throw "Index is outside of the vector's bounds";
	}
	return data[index];
}

std::ostream& operator<<(std::ostream& os, const NVector& vector)
{
	os << vector.size << ": ";
	for (size_t i = 0; i < vector.size; i++)
	{
		os << vector[i];
		if (i < vector.size - 1)
		{
			os << " ";
		}
	}
	return os;
}

std::istream& operator>>(std::istream& is, NVector& vector)
{
	size_t size = 0;
	is >> size;
	is.ignore();
	NVector result(size);

	for (size_t i = 0; i < size; i++)
	{
		is >> result[i];
	}
	vector = result;
	return is;
}

bool operator||(const NVector& first, const NVector& second)
{
	if (first.getLength() != second.getLength())
	{
		throw "The dimensions of the two vectors are not equal!";
	}

	double ratio = 0;
	bool isRatioSet = false;
	for (size_t i = 0; i < first.getLength(); i++)
	{
		if (second[i] == 0)
		{
			continue;
		}
		double currentRatio = (double)first[i] / second[i];
		if (isRatioSet && abs(ratio - currentRatio) > 1e-7)
		{
			return false;
		}

		isRatioSet = true;
		ratio = currentRatio;
	}
	return true;
}

bool operator|=(const NVector& first, const NVector& second)
{
	return first % second == 0;
}

NVector operator+(const NVector& first, const NVector& second)
{
	NVector result = first;
	result += second;
	return result;
}

NVector operator-(const NVector& first, const NVector& second)
{
	NVector result = first;
	result -= second;
	return result;
}

double operator%(const NVector& first, const NVector& second)
{
	if (first.getLength() != second.getLength())
	{
		throw "The dimensions of the two vectors are not equal!";
	}

	double result = 0;
	for (size_t i = 0; i < first.getLength(); i++)
	{
		result += first[i] * second[i];
	}
	return result;
}

NVector operator*(const NVector& vector, double scalar)
{
	NVector result = vector;
	result *= scalar;
	return result;
}

NVector operator*(double scalar, const NVector& vector)
{
	return vector * scalar;
}
