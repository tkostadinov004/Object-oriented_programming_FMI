#include <iostream>
#include <fstream>

int main()
{
	std::ifstream file("Task 1 - Self Reading.cpp");
	if (!file.is_open())
	{
		return -1;
	}

	while (!file.eof())
	{
		char buffer[1024];
		file.getline(buffer, 1024);

		std::cout << buffer << std::endl;
	}
}