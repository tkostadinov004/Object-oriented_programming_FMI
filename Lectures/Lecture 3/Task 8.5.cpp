#include <iostream>

double addOne(double x)
{
	return x + 1;
}
double multTwo(double x)
{
	return x * 2;
}

double fmax(double(*f)(double), double(*g)(double), double x)
{
	double fVal = f(x);
	double gVal = g(x);
	return fVal >= gVal ? fVal : gVal;
}
int main()
{
	std::cout << fmax(addOne, multTwo, 5);
}