#include <iostream>
#include "NVector.h"
#include "CoordinateSystem.h"

int main()
{
	NVector v1(4);
	for (size_t i = 0; i < v1.getLength(); i++)
	{
		v1[i] = i + 1;
	}
	std::cout << v1 << std::endl;

	v1 *= 2;
	std::cout << v1 << std::endl;
	v1 *= 0.5;
	std::cout << v1 << std::endl;

	NVector v2(4);
	for (size_t i = 0; i < v2.getLength(); i++)
	{
		v2[i] = (i + 1) * 2;
	}
	std::cout << v2 << std::endl;
	std::cout << (v1 || v2) << std::endl;
	std::cout << (v1 |= v2) << std::endl;

	NVector p1(2), p2(2);
	p1[0] = 1;
	p1[1] = 2;
	p2[0] = 2;
	p2[1] = -1;

	std::cout << (p1 |= p2) << std::endl;

	NVector b1(4);
	b1[0] = 2;
	b1[1] = 1;

	NVector b2(4);
	b2[0] = 3;
	b2[1] = 1;
	CoordinateSystem s(b1, b2);

	std::cout << s.getVectorByCoordinates(7, 4) << std::endl; // [26, 11]

	std::cout << s.getCoordinatesByVector(7, 4) << std::endl; // [5, -1]

	NVector r;
	std::cin >> r;
	std::cout << r << std::endl;
}