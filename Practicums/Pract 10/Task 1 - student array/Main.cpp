#include <iostream>
#include "Student.h"
#include "StudentArray.h"

int main()
{
	Student s1("Student1", "FN1", Major::IS);
	Student s2("Student2", "FN2", Major::SI);

	StudentArray arr;
	arr.push_back(s1);
	arr.push_back(s2);

	std::cout << arr << std::endl;
	try
	{
		std::cout << arr.at(2);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	try
	{
		std::cout << arr.at(-1);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	arr.push_front(Student("Student3", "FN3", Major::M));
	std::cout << arr << std::endl;
	
	StudentArray arr2;
	try
	{
		std::cout << arr2.getFront() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	try
	{
		std::cout << arr2.getBack() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}