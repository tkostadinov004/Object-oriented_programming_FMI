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

int getMaxValueIndex(DoubleFunction* arr, size_t size, double num)
{
	if (!arr)
	{
		return -1;
	}

	double maxValue = INT_MIN;
	int maxIndex = -1;
	for (size_t i = 0; i < size; i++)
	{
		double current = arr[i](num);
		if (current > maxValue)
		{
			maxValue = current;
			maxIndex = i;
		}
	}
	return maxIndex;
}
int main()
{
	constexpr size_t SIZE = 5;
	DoubleFunction functions[SIZE] = { addOne, getSqrt, multTwo, subOne, divTwo };

	double x;
	std::cin >> x;

	std::cout << getMaxValueIndex(functions, SIZE, x);
}