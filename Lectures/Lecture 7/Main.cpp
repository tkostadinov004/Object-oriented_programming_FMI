#include <iostream>
#include "LList.cpp"

int main()
{
	LList<int> list;
	list.push(3);
	list.push(2);
	list.push(1);

	list.print();

	list.pop();
	list.pop();
	list.pop();
	list.pop(); // shouldn't remove

	for (int i = 1; i <= 20; i++)
	{
		list.push_back(i);
	}
	list.print();
	std::cout << list[0] << std::endl;
	std::cout << list[5] << std::endl;
	std::cout << list[19] << std::endl;
	std::cout << list[20] << std::endl;
	std::cout << list[21] << std::endl;

	LList<int> list2;
	list2.push_back(1);
	list2.push_back(2);
	list2.push_back(3);
	list2.push_back(1);
	list2.push_back(3);
	list2.push_back(3);
	list2.push_back(1);

	list += list2;
	list.print();

	list[0] = 1000;
	list[200] = 100; //shouldn't change
	list.print();

	list2.print();
	LList<int> mapped_list2 = list2.mapF([](const int& x) {return x * 2;}).mapF([](const int& x) {return x + 1;});
	list2.print();
	mapped_list2.print();

	list2.mapD([](const int& x) {return x + 1;});
	list2.print();

	std::cout << list2.reduce([](const int& accumulator, const int& currentValue) {return accumulator + currentValue;}, 0) << std::endl;

	list2.print();
	std::cout << list2.count(2) << std::endl;
	list2.removeAll(2);
	list2.print();
	std::cout << list2.count(3) << std::endl;
	list2.removeAll(3);
	list2.print();
	std::cout << list2.count(4) << std::endl;
	list2.removeAll(4);
	list2.print();

	std::cout << list2.count(4) << std::endl; // 0

	LList<int> list3;
	for (int i = 1; i <= 5; i++)
	{
		list3.push(i);
	}
	list3.print();
	list3.insertAt(0, 100);
	list3.print();
	list3.insertAt(2, 200);
	list3.print();
	list3.insertAt(6, 300);
	list3.print();
	list3.insertAt(8, 500);
	list3.print();
	list3.insertAt(10, 700); //shouldn't add
	list3.print();
}