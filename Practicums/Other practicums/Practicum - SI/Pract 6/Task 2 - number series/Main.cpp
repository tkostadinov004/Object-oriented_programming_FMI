#include <iostream>
#include "NumberSeries.h"

int main()
{
	NumberSeries ns(1, [](int n) {return n * 2;});
	std::cout << ns.getNumber(10) << std::endl;
	std::cout << ns.getNumber(5) << std::endl; // should return the result without calculating it again

	std::cout << ns.isInSequence(1) << std::endl;
	std::cout << ns.isInSequence(2) << std::endl;
	std::cout << ns.isInSequence(512) << std::endl;
	std::cout << ns.isInSequence(1024) << std::endl;
	std::cout << ns.isInSequence(1025) << std::endl;
}