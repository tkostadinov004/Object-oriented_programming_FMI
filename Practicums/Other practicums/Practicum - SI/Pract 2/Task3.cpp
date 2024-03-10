#include <iostream>
#include <fstream>
using namespace std;

constexpr size_t BUFFER_LENGTH = 1024;
int main()
{
	std::ifstream ifs("Task3.cpp");
	if (!ifs.is_open())
	{
		return -1;
	}

	while (!ifs.eof())
	{
		char buffer[BUFFER_LENGTH];
		ifs.getline(buffer, BUFFER_LENGTH);

		cout << buffer << endl;
	}
}