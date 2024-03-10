#include <iostream>
#include <fstream>
using namespace std;
constexpr size_t MAX_COUNT = 64;

unsigned getNumOccurrences(const int* arr, int num, size_t size)
{
	if (!arr)
	{
		return 0;
	}

	unsigned count = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (arr[i] == num)
		{
			count++;
		}
	}
	return count;
}
void readNumbers(std::ifstream& ifs, int* arr, size_t& size)
{
	if (!arr)
	{
		return;
	}

	ifs >> size;
	int index = 0;
	while (!ifs.eof())
	{
		ifs >> arr[index++];
	}
}
int getMostCommonNumber(const int* arr, size_t size)
{
	if (!arr)
	{
		return -1;
	}

	unsigned mostOccurrences = 0;
	int mostCommonNum = 0;
	for (size_t i = 0; i < size; i++)
	{
		unsigned currentOccs = getNumOccurrences(arr, arr[i], size);
		if (currentOccs > mostOccurrences)
		{
			mostOccurrences = currentOccs;
			mostCommonNum = arr[i];
		}
	}
	return mostCommonNum;
}
int getMostCommonNumber(const char* filename)
{
	if (!filename)
	{
		return -1;
	}
	std::ifstream ifs(filename);
	if (!ifs.is_open())
	{
		return -1;
	}

	int arr[MAX_COUNT];
	size_t size;
	readNumbers(ifs, arr, size);

	return getMostCommonNumber(arr, size);
}
int main()
{
	cout << getMostCommonNumber("nums.txt");
}