#include <cmath>
#include "HelperFunctions.h"

bool isPowerOfTwo(unsigned n)
{
	return (n & (n - 1)) == 0;
}

unsigned getNextPowerOfTwo(unsigned n)
{
	if (n == 0)
	{
		return 1;
	}

	if (isPowerOfTwo(n))
	{
		return n << 1;
	}
	return 1 << (unsigned)ceil(log2(n));
}
