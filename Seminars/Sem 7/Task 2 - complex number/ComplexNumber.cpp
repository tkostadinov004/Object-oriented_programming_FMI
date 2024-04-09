#include "ComplexNumber.h"

ComplexNumber::ComplexNumber(double real, double imaginary)
{
    setReal(real);
    setImaginary(imaginary);
}

double ComplexNumber::getReal() const
{
    return real;
}

double ComplexNumber::getImaginary() const
{
    return imaginary;
}

void ComplexNumber::setReal(double value)
{
    this->real = value;
}

void ComplexNumber::setImaginary(double value)
{
    this->imaginary = value;
}

ComplexNumber& ComplexNumber::operator+=(const ComplexNumber& number)
{
    this->real += number.real;
    this->imaginary += number.imaginary;

    return *this;
}

ComplexNumber& ComplexNumber::operator-=(const ComplexNumber& number)
{
    this->real -= number.real;
    this->imaginary -= number.imaginary;

    return *this;
}

ComplexNumber& ComplexNumber::operator*=(const ComplexNumber& number)
{
    double newReal = this->real * number.real - this->imaginary * number.imaginary;
    this->imaginary = this->real * number.imaginary + this->imaginary * number.real;
    this->real = newReal;
    return *this;
}

ComplexNumber& ComplexNumber::operator/=(const ComplexNumber& number)
{
    if (number.real == 0 && number.imaginary == 0)
    {
        return *this;
    }

    ComplexNumber conjugate(number.real, -number.imaginary);
    *this *= conjugate;
    this->real /= (number.real * number.real + number.imaginary * number.imaginary);
    this->imaginary /= (number.real * number.real + number.imaginary * number.imaginary);

    return *this;
}

ComplexNumber operator+(const ComplexNumber& lhs, const ComplexNumber& rhs)
{
    ComplexNumber result(lhs);
    result += rhs;
    return result;
}

ComplexNumber operator-(const ComplexNumber& lhs, const ComplexNumber& rhs)
{
    ComplexNumber result(lhs);
    result -= rhs;
    return result;
}

ComplexNumber operator*(const ComplexNumber& lhs, const ComplexNumber& rhs)
{
    ComplexNumber result(lhs);
    result *= rhs;
    return result;
}

ComplexNumber operator/(const ComplexNumber& lhs, const ComplexNumber& rhs)
{
    if (rhs.getReal() == 0 && rhs.getImaginary() == 0)
    {
        throw "Attemped division by zero!";
    }
    ComplexNumber result(lhs);
    result /= rhs;
    return result;
}

std::ostream& operator<<(std::ostream& os, const ComplexNumber& number)
{
    os << number.getReal() << " + " << number.getImaginary() << "i";
    return os;
}

std::istream& operator>>(std::istream& is, ComplexNumber& number)
{
    double real = 0, imaginary = 0;
    is >> real >> imaginary;
    number.setReal(real);
    number.setImaginary(imaginary);
    return is;
}
