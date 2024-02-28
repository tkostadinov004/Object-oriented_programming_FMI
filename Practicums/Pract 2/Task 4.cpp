#include <iostream>
using namespace std;

struct ComplexNumber
{
    double real;
    double imaginary;
    void print() const
    {
        cout << real << " + " << imaginary << "i" << endl;
    }
    double getAbsoluteValue() const
    {
        return sqrt(real * real + imaginary * imaginary);
    }
};
void addComplex(ComplexNumber& first, const ComplexNumber& second)
{
    first.real += second.real;
    first.imaginary += second.imaginary;
}
void multiplyComplex(ComplexNumber& first, const ComplexNumber& second)
{
    int resultReal = first.real * second.real - first.imaginary * second.imaginary;
    int resultImaginary = first.real * second.imaginary + first.imaginary * second.real;

    first.real = resultReal;
    first.imaginary = resultImaginary;
}
int main()
{
    ComplexNumber c1{ 5, -2 };
    ComplexNumber c2{ -3, 7 };

    c1.print();
    c2.print();

    cout << c1.getAbsoluteValue() << endl;
    cout << c2.getAbsoluteValue() << endl;

    addComplex(c1, c2);
    c1.print();

    multiplyComplex(c1, c2);
    c1.print();
}