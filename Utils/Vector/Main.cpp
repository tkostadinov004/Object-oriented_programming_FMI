#include <iostream>
#include "MyVector.hpp"

int main()
{
	MyVector<int> v;
	MyVector<int> v2(5);
	MyVector<int> v3 = v2;

	std::cout << v.size() << std::endl;
	std::cout << v.capacity() << std::endl;
	std::cout << v2.size() << std::endl;
	std::cout << v2.capacity() << std::endl;
	std::cout << v3.size() << std::endl;
	std::cout << v3.capacity() << std::endl;

	try
	{
		v.at(0);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	v.clear();
	for (size_t i = 0; i < 9; i++)
	{
		v.push_back(i);
	}
	std::cout << v << std::endl;
	std::cout << v.at(0) << std::endl;
	std::cout << v.at(4) << std::endl;
	std::cout << v.at(8) << std::endl;
	v2.push_back(0);
	v2.push_back(0);
	v2.push_back(0);
	v2.push_back(0);
	v2.push_back(0);
	v.append_range(v2);

	v3 = v;

	std::cout << v << std::endl;
	v.erase(0);
	std::cout << v << std::endl;
	v.erase(3);
	std::cout << v << std::endl;
	v.erase(2, 5);
	std::cout << v << std::endl;
	v = v3;
	std::cout << v << std::endl;
	v.erase(0, v.size() - 1);
	std::cout << v << std::endl;
	v = v3;
	std::cout << v << std::endl;
	v.erase(v.size() - 1, v.size() - 1);
	std::cout << v << std::endl;
	v = v3;
	std::cout << v << std::endl;
	v.erase(v.size() - 1, v.size() + 100);
	std::cout << v << std::endl;
	
	v = v3;
	v.insert(0, 1000);
	std::cout << v << std::endl;
	v.insert(v.size() - 1, 2000);
	std::cout << v << std::endl;
	v.insert(v.size(), 3000);
	std::cout << v << std::endl;
	v.insert(v.size() + 20000, 3000);
	std::cout << v << std::endl;

	MyVector<int> v4;
	v4.append(-20, 5);
	v.insert_range(0, v4);
	std::cout << v << std::endl;
	v.insert_range(v.size() - 1, v4);
	std::cout << v << std::endl;
	v.erase(0, 4);
	std::cout << v << std::endl;
	v.erase(v.size() - 6, v.size() - 2);
	std::cout << v << std::endl;
	v.insert_range(v.size(), v4);
	std::cout << v << std::endl;
	v.insert_range(v.size() + 100, v4);
	std::cout << v << std::endl;

	v.insert_range(0, v);
	std::cout << v << std::endl;
	
	std::cout << v4 << std::endl;
	v4.pop_back();
	std::cout << v4 << std::endl;
	v4.pop_back();
	std::cout << v4 << std::endl;
	v4.pop_back();
	std::cout << v4 << std::endl;
	v4.pop_back();
	std::cout << v4 << std::endl;
	v4.pop_back();
	std::cout << v4 << std::endl;
	
	std::cout << v4.empty() << std::endl;
	v4.append(100, 100);
	std::cout << v4.size() << std::endl;
	std::cout << v4.capacity() << std::endl;
	v4.clear();
	std::cout << v4.size() << std::endl;
	std::cout << v4.capacity() << std::endl;
	v4.shrink_to_fit();
	std::cout << v4.size() << std::endl;
	std::cout << v4.capacity() << std::endl;
	v4.push_back(1);
	std::cout << v4.size() << std::endl;
	std::cout << v4.capacity() << std::endl;
	v4.push_back(2);
	std::cout << v4.size() << std::endl;
	std::cout << v4.capacity() << std::endl;
	v4.push_back(2);
	std::cout << v4.size() << std::endl;
	std::cout << v4.capacity() << std::endl;
	v4.push_back(2);
	std::cout << v4.size() << std::endl;
	std::cout << v4.capacity() << std::endl;
	v4.push_back(2);
	std::cout << v4.size() << std::endl;
	std::cout << v4.capacity() << std::endl;

	MyVector<int> v5, v6;
	for (size_t i = 0; i < 10; i++)
	{
		v5.push_back(i);
		v6.push_back(i + 1);
	}
	std::cout << (v5 == v5) << std::endl;
	std::cout << (v5 != v5) << std::endl;
	std::cout << (v5 < v5) << std::endl;
	std::cout << (v5 <= v5) << std::endl;
	std::cout << (v5 > v5) << std::endl;
	std::cout << (v5 >= v5) << std::endl;

	std::cout << (v5 == v6) << std::endl;
	std::cout << (v5 != v6) << std::endl;
	std::cout << (v5 < v6) << std::endl;
	std::cout << (v5 <= v6) << std::endl;
	std::cout << (v5 > v6) << std::endl;
	std::cout << (v5 >= v6) << std::endl;

	std::cout << (v6 == v5) << std::endl;
	std::cout << (v6 != v5) << std::endl;
	std::cout << (v6 < v5) << std::endl;
	std::cout << (v6 <= v5) << std::endl;
	std::cout << (v6 > v5) << std::endl;
	std::cout << (v6 >= v5) << std::endl;
}