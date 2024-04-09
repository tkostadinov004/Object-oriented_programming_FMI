#pragma once
#include <iostream>

class ComplexNumber
{
	double real = 0;
	double imaginary = 0;
public:
	ComplexNumber() = default;
	ComplexNumber(double real, double imaginary);

	double getReal() const;
	double getImaginary() const;

	void setReal(double value);
	void setImaginary(double value);

	ComplexNumber& operator+=(const ComplexNumber& number);
	ComplexNumber& operator-=(const ComplexNumber& number);
	ComplexNumber& operator*=(const ComplexNumber& number);
	ComplexNumber& operator/=(const ComplexNumber& number);
};
ComplexNumber operator+(const ComplexNumber& lhs, const ComplexNumber& rhs);
ComplexNumber operator-(const ComplexNumber& lhs, const ComplexNumber& rhs);
ComplexNumber operator*(const ComplexNumber& lhs, const ComplexNumber& rhs);
ComplexNumber operator/(const ComplexNumber& lhs, const ComplexNumber& rhs);

std::ostream& operator<<(std::ostream& os, const ComplexNumber& number);
std::istream& operator>>(std::istream& is, ComplexNumber& number);