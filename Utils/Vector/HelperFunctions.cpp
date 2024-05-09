#include <iostream>
#include "HelperFunctions.h"

bool HelperFunctions::isPowerOfTwo(unsigned num)
{
	return (num & (num - 1)) == 0;
}

unsigned HelperFunctions::getNextPowerOfTwo(unsigned num)
{
	return isPowerOfTwo(num) ? num << 1 : 1 << (unsigned)ceil(log2(num));
}