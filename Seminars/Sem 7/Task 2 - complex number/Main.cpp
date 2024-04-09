#include <iostream>
#include "ComplexNumber.h"

int main()
{
	ComplexNumber c;
	std::cin >> c;

	ComplexNumber c2;
	std::cin >> c2;

	ComplexNumber result = c / c2;
	ComplexNumber resultM = c * c2;

	std::cout << result << std::endl;
	std::cout << resultM << std::endl;
}