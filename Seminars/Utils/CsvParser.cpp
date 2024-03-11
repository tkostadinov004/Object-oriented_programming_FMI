#include <iostream>
#include <fstream>
#include <sstream>
#pragma warning (disable: 4996)
using namespace std;

namespace Constants
{
	constexpr size_t MAX_CONTENT_LENGTH = 50;
	constexpr size_t MAX_RECORDS_COUNT = 200;
	constexpr size_t BUFFER_SIZE = 1024;
}

using Field = char[Constants::MAX_CONTENT_LENGTH];

struct Row
{
	Field fields[Constants::MAX_CONTENT_LENGTH];
};
struct CsvTable
{
	Row records[Constants::MAX_RECORDS_COUNT];
	size_t recordsCount = 0;
	size_t columnsCount = 0;
};
size_t parseRow(const char* rowContent, Row& row)
{
	if (!rowContent)
	{
		return 0;
	}

	stringstream sts(rowContent);

	size_t colIndex = 0;
	while (!sts.eof())
	{
		sts.getline(row.fields[colIndex++], Constants::MAX_CONTENT_LENGTH, ',');
	}
	return colIndex;
}
void parseCsvTable(std::ifstream& ifs, CsvTable& csvTable)
{
	char buffer[Constants::BUFFER_SIZE];

	while (!ifs.eof())
	{
		ifs.getline(buffer, Constants::BUFFER_SIZE);
		csvTable.columnsCount = parseRow(buffer, csvTable.records[csvTable.recordsCount++]);
	}
}
void parseCsvTable(const char* src, CsvTable& csvTable)
{
	if (!src)
	{
		return;
	}

	std::ifstream ifs(src);
	if (!ifs.is_open())
	{
		return;
	}

	parseCsvTable(ifs, csvTable);
}
void serializeRow(std::ofstream& ofs, const Row& row, size_t columnCount)
{
	for (size_t i = 0; i < columnCount; i++)
	{
		ofs << row.fields[i];
		if (i < columnCount - 1)
		{
			ofs << ',';
		}
	}
	ofs << endl;
}
void saveToFile(std::ofstream& ofs, const CsvTable& csvTable)
{
	for (size_t i = 0; i < csvTable.recordsCount; i++)
	{
		serializeRow(ofs, csvTable.records[i], csvTable.columnsCount);
	}
}
void saveToFile(const char* dest, const CsvTable& csvTable)
{
	if (!dest)
	{
		return;
	}
	
	std::ofstream ofs(dest);
	if (!ofs.is_open())
	{
		return;
	}
	
	saveToFile(ofs, csvTable);
}
int main()
{
	CsvTable table{};
	parseCsvTable("info.csv", table);

	saveToFile("info1.csv", table);
}