#include <iostream>

using DoubleFunction = double(*)(double);
double addOne(double x)
{
	return x + 1;
}
double getSqrt(double x)
{
	return sqrt(x);
}
double multTwo(double x)
{
	return x * 2;
}
double subOne(double x)
{
	return x - 1;
}
double divTwo(double x)
{
	return x / 2;
}

double fmax(double(*f)(double), double(*g)(double), double x)
{
	double fVal = f(x);
	double gVal = g(x);
	return fVal >= gVal ? fVal : gVal;
}
double myMax(double a, double b)
{
	return a >= b ? a : b;
}
double maxarray(DoubleFunction* array, int n, double x)
{
	if (!array)
	{
		return -1;
	}

	double maxValue = INT_MIN;
	for (size_t i = 0; i < n - 1; i++)
	{
		double current = array[i](x);
		if (current > maxValue)
		{
			maxValue = current;
		}
		//maxValue = myMax(fmax(array[i], array[i + 1], x), maxValue);
	}
	return maxValue;
}
int main()
{
	constexpr size_t SIZE = 5;
	DoubleFunction functions[SIZE] = { addOne, getSqrt, multTwo, subOne, divTwo };

	double x;
	std::cin >> x;

	std::cout << maxarray(functions, SIZE, x);
}