#include <iostream>
#include <fstream>
#pragma warning (disable: 4996)
using namespace std;

void printDifference(std::ifstream& ifs1, std::ifstream& ifs2)
{
	char firstFileLine[1024] = { 0 };
	char secondFileLine[1024] = { 0 };
	bool isDifference = false;
	while (!ifs1.eof() && !ifs2.eof())
	{
		ifs1.getline(firstFileLine, 1024);
		ifs2.getline(secondFileLine, 1024);

		if (strcmp(firstFileLine, secondFileLine) != 0)
		{
			isDifference = true;
			break;
		}
	}

	if (ifs1.eof() && !ifs2.eof())
	{
		strcpy(firstFileLine, "EOF");
		ifs2.getline(secondFileLine, 1024);
		isDifference = true;
	}
	else if (ifs2.eof() && !ifs1.eof())
	{
		strcpy(secondFileLine, "EOF");
		ifs1.getline(firstFileLine, 1024);
		isDifference = true;
	}

	if (isDifference)
	{
		std::cout << "First file: " << firstFileLine << std::endl;
		std::cout << "Second file: " << secondFileLine << std::endl;
	}
	else
	{
		std::cout << "No difference!" << std::endl;
	}
}
void printDifference(const char* first, const char* second)
{
	if (!first || !second)
	{
		return;
	}

	std::ifstream ifs1(first);
	if (!ifs1.is_open())
	{
		return;
	}

	std::ifstream ifs2(second);
	if (!ifs2.is_open())
	{
		return;
	}

	printDifference(ifs1, ifs2);
}
int main()
{
	printDifference("first.txt", "second.txt");
}