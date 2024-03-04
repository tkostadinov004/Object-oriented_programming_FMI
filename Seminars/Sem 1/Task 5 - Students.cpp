#include <iostream>
#include <fstream>
#pragma warning (disable: 4996)

enum class Major
{
	Informatics, IS, CS, SoftEng, Math, AppliedMath, Statistics, DataAnalysis
};
struct Student
{
	char name[100];
	char fn[15];
	Major major;
	unsigned year;
};
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

void outputStudent(const Student& student, std::ostream& stream)
{
	stream << student.name << "|" << student.fn << " " << (int)student.major << " " << student.year << std::endl;
}
void save(const Student* students, size_t size, const char* dest)
{
	if (!students || !dest)
	{
		return;
	}

	std::ofstream ofs(dest);
	if (!ofs.is_open())
	{
		return;
	}

	for (size_t i = 0; i < size; i++)
	{
		outputStudent(students[i], ofs);
	}
}
Student readStudent(std::ifstream& file)
{
	Student student{};

	char nameBuffer[100];
	file.getline(nameBuffer, 100, '|');
	strcpy(student.name, nameBuffer);

	char fnBuffer[20];
	file.getline(fnBuffer, 20, ' ');
	strcpy(student.fn, fnBuffer);

	int majorNum;
	file >> majorNum;
	student.major = (Major)majorNum;

	file >> student.year;
	file.ignore();

	return student;
}
Student* read(const char* src, size_t& size)
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

	size = getCharOccurrences(file, '\n');
	file.clear();
	file.seekg(0, std::ios::beg);

	Student* students = new Student[size];

	for (size_t i = 0; i < size; i++)
	{
		students[i] = readStudent(file);
	}
	return students;
}
int main()
{
	//Student output[] = { {"Georgi Popov", "0MI23125345", Major::IS, 1}, {"Ivan Ivanovich Ivanov", "2MI23645345", Major::Informatics, 4}, {"Test Test", "1MI12325345", Major::Math, 2} };
	//save(output, 3, "students.txt");

	size_t size = 0;
	Student* students = read("students.txt", size);

	for (size_t i = 0; i < size; i++)
	{
		outputStudent(students[i], std::cout);
	}
	delete[] students;
}