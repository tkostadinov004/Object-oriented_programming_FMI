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
int* getArrayFromFile(const char* src, size_t& size)
{
	if (!src)
	{
		return nullptr;
	}

	std::ifstream file(src);
	if (!file.is_open())
	{
		return nullptr;
	}
	size = getCharOccurrences(file, ' ') + 1;

	file.clear();
	file.seekg(0, std::ios::beg);

	int* arr = new int[size];

	for (size_t i = 0; i < size; i++)
	{
		file >> arr[i];
	}
	return arr;
}
int* mergeSorted(const int* first, size_t firstSize, const int* second, size_t secondSize)
{
	if (!first || !second)
	{
		return nullptr;
	}

	int* result = new int[firstSize + secondSize];
	int index = 0;

	int i = 0, j = 0;
	while (i < firstSize && j < secondSize)
	{
		if (first[i] < second[j])
		{
			result[index++] = first[i++];
		}
		else
		{
			result[index++] = second[j++];
		}
	}
	while (i < firstSize)
	{
		result[index++] = first[i++];
	}
	while (j < secondSize)
	{
		result[index++] = second[j++];
	}

	return result;
}
void mergeFiles(const char* numsFile1Path, const char* numsFile2Path, const char* dest)
{
	if (!numsFile1Path || !numsFile2Path || !dest)
	{
		return;
	}

	size_t firstSize, secondSize;
	int* first = getArrayFromFile(numsFile1Path, firstSize);
	int* second = getArrayFromFile(numsFile2Path, secondSize);

	int* result = mergeSorted(first, firstSize, second, secondSize);

	std::ofstream resultStream(dest);
	if (!resultStream.is_open())
	{
		delete[] first;
		delete[] second;
		delete[] result;
		return;
	}

	for (size_t i = 0; i < firstSize + secondSize; i++)
	{
		resultStream << result[i] << " ";
	}
	delete[] first;
	delete[] second;
	delete[] result;
}
int main()
{
	mergeFiles("1.txt", "2.txt", "result.txt");
}