#include <iostream>
#include "MyString.h"
#include "StringVector.h"

int main()
{
	MyString str1 = "example";
	MyString str2 = "test";
	MyString str3 = "walk 2";
	MyString str4 = "c++ is great";

	StringVector vector;
	std::cout << vector.empty() << std::endl;
	vector.push_back(str1);
	std::cout << vector.empty() << std::endl;
	vector.push_back(str2);
	vector.push_back(str3);
	vector.push_back(str4);

	std::cout << vector << std::endl;
	vector.insert("asdasd", 0);
	std::cout << vector << std::endl;
	vector.insert("atf", 1);
	std::cout << vector << std::endl;
	vector.insert("fail? no!", vector.size() - 1);
	std::cout << vector << std::endl;

	vector.erase(3);
	std::cout << vector << std::endl;
	vector.pop_back();
	std::cout << vector << std::endl;
	
	StringVector vector2;
	std::cin >> vector2;
	std::cout << vector2 << std::endl;
}