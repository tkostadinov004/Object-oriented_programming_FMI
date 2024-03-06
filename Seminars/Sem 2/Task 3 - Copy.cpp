#include <iostream>
#include <fstream>

constexpr size_t BUFFER_SIZE = 1024;

void copyTo(const char* src, const char* dest)
{
	if (!src || !dest)
	{
		return;
	}

	std::ifstream ifs(src);
	std::ofstream ofs(dest);
	if (!ifs.is_open() || !ofs.is_open())
	{
		return;
	}

	while (!ifs.eof())
	{
		char buffer[BUFFER_SIZE];
		ifs.getline(buffer, BUFFER_SIZE);

		ofs << buffer << std::endl;
	}
}
int main()
{
	copyTo("Task 3 - Copy.cpp", "test.txt");
}