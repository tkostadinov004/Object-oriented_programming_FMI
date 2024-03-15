#include <iostream>
#include <fstream>
#pragma warning (disable: 4996)

const char* DEFAULT_FILE_NAME = "myData.dat";
struct HexViewerFile
{
	char* data;
	size_t dataSize = 0;
};
size_t getFileSize(std::ifstream& ifs)
{
	int currentPos = ifs.tellg();
	ifs.seekg(0, std::ios::end);
	size_t size = ifs.tellg();

	ifs.clear();
	ifs.seekg(currentPos);

	return size;
}
char getHexDigit(unsigned value)
{
	if (value < 10)
	{
		return '0' + value;
	}
	return 'a' + (value - 10);
}
void printHex(unsigned char value)
{
	std::cout << getHexDigit(value / 16) << getHexDigit(value % 16);
}
void view(const HexViewerFile& file)
{
	for (size_t i = 0; i < file.dataSize; i++)
	{
		printHex(file.data[i]);
		std::cout << " ";
		if ((i + 1) % 16 == 0)
		{
			std::cout << std::endl;
		}
	}
	std::cout << std::endl << std::endl;

	for (size_t i = 0; i < file.dataSize; i++)
	{
		if (isalpha((unsigned char)file.data[i]))
		{
			std::cout << file.data[i];
		}
		else
		{
			std::cout << '.';
		}

		if ((i + 1) % 16 == 0)
		{
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}
void changeByte(HexViewerFile& file, int index, unsigned char newValue)
{
	file.data[index] = newValue;
}
void remove(HexViewerFile& file)
{
	file.data[--file.dataSize] = 0;
}
void add(HexViewerFile& file)
{
	char* temp = new char[file.dataSize + 1];
	for (size_t i = 0; i < file.dataSize; i++)
	{
		temp[i] = file.data[i];
	}
	temp[file.dataSize++] = 0;

	delete[] file.data;
	file.data = temp;
}
void saveAs(std::ofstream& ofs, const HexViewerFile& file)
{
	ofs.write(file.data, file.dataSize);
}
void saveAs(const char* filename, const HexViewerFile& file)
{
	if (!filename)
	{
		return;
	}

	std::ofstream ofs(filename, std::ios::binary);
	if (!ofs.is_open())
	{
		return;
	}

	saveAs(ofs, file);
}
void save(const HexViewerFile& file)
{
	saveAs(DEFAULT_FILE_NAME, file);
}
HexViewerFile initializeFile()
{
	std::ifstream ifs(DEFAULT_FILE_NAME, std::ios::binary);
	if (!ifs.is_open())
	{
		return {};
	}

	HexViewerFile file{};
	file.dataSize = getFileSize(ifs);
	file.data = new char[file.dataSize];
	ifs.read(file.data, file.dataSize);

	return file;
}
int main()
{
	HexViewerFile file = initializeFile();

	view(file);

	changeByte(file, 0, 'F');
	view(file);

	remove(file);
	view(file);

	add(file);
	add(file);
	view(file);

	save(file);
	saveAs("myData2.dat", file);

	delete[] file.data;
}