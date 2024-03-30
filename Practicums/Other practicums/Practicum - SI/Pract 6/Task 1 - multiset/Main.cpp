#include <iostream>
#include "MultiSet.h"

int main()
{
	MultiSet set1(64);
	set1.add(4);
	set1.add(5);
	set1.add(7);
	set1.add(999); // shouldn't add
	set1.add(7);
	set1.add(0);
	set1.print();

	MultiSet set2(42);
	set2.add(4);
	set2.add(7);
	set2.add(41);
	set2.add(41);
	set1.add(999); // shouldn't add
	set2.add(7);
	set2.add(7);
	set2.add(7); //shouldn't add
	set2.add(0);
	set2.print();

	getIntersection(set1, set2).print();
	getUnion(set1, set2).print();
}