#include <iostream>
#include <fstream>

unsigned getCharOccurrences(std::ifstream& file, char c)
{
	unsigned count = 0;
	while (true)
	{
		char current = file.get();
		if (file.eof())
		{
			break;
		}
		if (current == c)
		{
			count++;
		}
	}
	return count;
}
unsigned getLinesCount(const char* filename)
{
	if (!filename)
	{
		return 0;
	}

	std::ifstream file(filename);
	if (!file.is_open())
	{
		return 0;
	}

	return getCharOccurrences(file, '\n') + 1;
}
int main()
{
	std::cout << getLinesCount("Task 2 - Lines count.cpp");
}