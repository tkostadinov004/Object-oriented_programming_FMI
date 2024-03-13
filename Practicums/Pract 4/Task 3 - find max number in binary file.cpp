#include <iostream>
#include <fstream>

size_t getFileSize(std::ifstream& ifs)
{
	int currentPos = ifs.tellg();
	ifs.seekg(0, std::ios::end);
	size_t size = ifs.tellg();

	ifs.clear();
	ifs.seekg(currentPos);

	return size;
}
int getMax(std::ifstream& ifs)
{
	size_t numsCount = getFileSize(ifs) / sizeof(int);

	int max = INT_MIN;
	for(size_t i = 0; i < numsCount; i++)
	{
		int current = 0;
		ifs.read((char*)&current, sizeof(current));

		if (current > max)
		{
			max = current;
		}
	}
	return max;
}
int main()
{
	std::ifstream ifs("nums.dat", std::ios::binary);

	if (!ifs.is_open())
	{
		return -1;
	}

	std::cout << getMax(ifs);
}