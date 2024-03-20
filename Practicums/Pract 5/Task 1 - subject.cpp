#include <iostream>
#include <fstream>
#pragma warning (disable: 4996)

constexpr size_t MAX_STUDENTS_COUNT = 100;
constexpr size_t FACULTY_NUMBER_LENGTH = 10;
constexpr size_t MAX_GRADES_COUNT = 32;

enum class Department
{
	Undefined,
	Algebra,
	Geometry,
	ComputerScience
};
void setStr(char*& dest, const char* src)
{
	if (!src)
	{
		return;
	}

	delete[] dest;
	dest = new char[strlen(src) + 1];
	strcpy(dest, src);
}
struct Student
{
private:
	char* firstName = nullptr;
	char* lastName= nullptr;
	size_t gradesCount;
	float grades[MAX_GRADES_COUNT];
	char facultyNumber[FACULTY_NUMBER_LENGTH + 1];
	void copyGrades(const float* grades, size_t size)
	{
		if (!grades || size > MAX_GRADES_COUNT)
		{
			return;
		}
		for (size_t i = 0; i < size; i++)
		{
			this->grades[i] = grades[i];
		}
	}
	void setFacultyNumber(char* dest, const char* src) const
	{
		if (!src)
		{
			return;
		}

		if (strlen(src) != FACULTY_NUMBER_LENGTH)
		{
			return;
		}
		strcpy(dest, src);
	}
public:
	Student() : Student("Undefined", "Undefined", 0, { 0 }, "Undefined") {}
	Student(const char* firstName, const char* lastName, const float* grades, size_t gradesCount, const char* facultyNumber)
	{
		setStr(this->firstName, firstName);
		setStr(this->lastName, lastName);
		setFacultyNumber(this->facultyNumber, facultyNumber);
		this->gradesCount = gradesCount;
		this->copyGrades(grades, gradesCount);
	}
	~Student()
	{
		delete[] firstName;
		delete[] lastName;
	}
	const char* getFirstName() const
	{
		return this->firstName;
	}
	const char* getLastName() const
	{
		return this->lastName;
	}
	const char* getFacultyNumber() const
	{
		return this->facultyNumber;
	}
	const float* getGrades() const
	{
		return this->grades;
	}
	bool addGrade(float grade)
	{
		if (this->gradesCount + 1 > MAX_GRADES_COUNT)
		{
			return false;
		}

		if (grade < 2 || grade > 6)
		{
			return false;
		}
		this->grades[gradesCount++] = grade;
		return true;
	}
	bool removeGrade()
	{
		if (gradesCount == 0)
		{
			return false;
		}

		this->grades[gradesCount--] = 0;
		return true;
	}
	float getGPA() const
	{
		float sum = 0;
		for (size_t i = 0; i < this->gradesCount; i++)
		{
			sum += this->grades[i];
		}
		return sum / this->gradesCount;
	}
	void serialize(std::ofstream& ofs) const
	{
		size_t firstNameLen = strlen(firstName);
		ofs.write((const char*)&firstNameLen, sizeof(firstNameLen));
		ofs.write(firstName, firstNameLen + 1);

		size_t lastNameLen = strlen(lastName);
		ofs.write((const char*)&lastNameLen, sizeof(lastNameLen));
		ofs.write(lastName, lastNameLen + 1);

		ofs.write(facultyNumber, FACULTY_NUMBER_LENGTH + 1);

		ofs.write((const char*)&gradesCount, sizeof(gradesCount));
		ofs.write((const char*)grades, sizeof(float) * MAX_GRADES_COUNT);
	}
	void deserialize(std::ifstream& ifs)
	{
		size_t firstNameLen = 0;
		ifs.read((char*)&firstNameLen, sizeof(firstNameLen));

		this->firstName = new char[firstNameLen + 1];
		ifs.read(this->firstName, firstNameLen + 1);

		size_t lastNameLen = 0;
		ifs.read((char*)&lastNameLen, sizeof(lastNameLen));
		this->lastName = new char[lastNameLen + 1];
		ifs.read(lastName, lastNameLen + 1);

		ifs.read(facultyNumber, FACULTY_NUMBER_LENGTH + 1);

		ifs.read((char*)&gradesCount, sizeof(gradesCount));
		ifs.read((char*)grades, sizeof(float) * MAX_GRADES_COUNT);
	}
	void copyTo(Student& other) const
	{
		setStr(other.firstName, this->firstName);
		setStr(other.lastName, this->lastName);
		setFacultyNumber(other.facultyNumber, this->facultyNumber);
		other.gradesCount = this->gradesCount;
		other.copyGrades(this->grades, this->gradesCount);
	}
};
struct Teacher
{
private:
	char* firstName = nullptr;
	char* lastName = nullptr;
	Department department = Department::Undefined;
public:
	Teacher() : Teacher("Undefined", "Undefined", Department::Undefined)
	{

	}
	Teacher(const char* firstName, const char* lastName, Department department)
	{
		setStr(this->firstName, firstName);
		setStr(this->lastName, lastName);
		this->department = department;
	}
	~Teacher()
	{
		delete[] firstName;
		delete[] lastName;
	}
	const char* getFirstName() const
	{
		return this->firstName;
	}
	const char* getLastName() const
	{
		return this->lastName;
	}
	Department getDepartment() const
	{
		return this->department;
	}
	void serialize(std::ofstream& ofs) const
	{
		size_t firstNameLen = strlen(firstName);
		ofs.write((const char*)&firstNameLen, sizeof(firstNameLen));
		ofs.write(firstName, firstNameLen + 1);

		size_t lastNameLen = strlen(lastName);
		ofs.write((const char*)&lastNameLen, sizeof(lastNameLen));
		ofs.write(lastName, lastNameLen + 1);

		ofs.write((const char*)&department, sizeof(department));
	}
	void deserialize(std::ifstream& ifs)
	{
		size_t firstNameLen = 0;
		ifs.read((char*)&firstNameLen, sizeof(firstNameLen));

		this->firstName = new char[firstNameLen + 1];
		ifs.read(this->firstName, firstNameLen + 1);

		size_t lastNameLen = 0;
		ifs.read((char*)&lastNameLen, sizeof(lastNameLen));
		this->lastName = new char[lastNameLen + 1];
		ifs.read(lastName, lastNameLen + 1);

		ifs.read((char*)&department, sizeof(department));
	}
	void copyTo(Teacher& other) const
	{
		setStr(other.firstName, this->firstName);
		setStr(other.lastName, this->lastName);
		other.department = this->department;
	}
};

struct Subject
{
private:
	Student students[MAX_STUDENTS_COUNT];
	size_t studentsCount;
	Teacher teacher;
	bool containsStudent(const Student& student)
	{
		for (size_t i = 0; i < this->studentsCount; i++)
		{
			if (strcmp(student.getFacultyNumber(), this->students[i].getFacultyNumber()) == 0)
			{
				return true;
			}
		}
		return false;
	}
	void serialize(std::ofstream& ofs) const
	{
		ofs.write((const char*)&studentsCount, sizeof(studentsCount));

		for (size_t i = 0; i < this->studentsCount; i++)
		{
			this->students[i].serialize(ofs);
		}
		this->teacher.serialize(ofs);
	}
	void deserialize(std::ifstream& ifs)
	{
		ifs.read((char*)&studentsCount, sizeof(studentsCount));

		for (size_t i = 0; i < this->studentsCount; i++)
		{
			this->students[i].deserialize(ifs);
		}
		this->teacher.deserialize(ifs);
	}
public:
	Subject() : studentsCount(0)
	{

	}
	Subject(const Student* students, size_t studentsCount, const Teacher& teacher) : Subject()
	{
		if (!students)
		{
			return;
		}

		for (size_t i = 0; i < studentsCount; i++)
		{
			addStudent(students[i]);
		}
		appointTeacher(teacher);
	}
	bool addStudent(const Student& student)
	{
		if (studentsCount + 1 > MAX_STUDENTS_COUNT)
		{
			return false;
		}

		if (this->containsStudent(student))
		{
			return false;
		}
		student.copyTo(this->students[studentsCount++]);
		return true;
	}
	void appointTeacher(const Teacher& teacher)
	{
		teacher.copyTo(this->teacher);
	}
	bool serialize(const char* filename) const
	{
		if (!filename)
		{
			return false;
		}

		std::ofstream ofs(filename, std::ios::binary);
		if (!ofs.is_open())
		{
			return false;
		}

		serialize(ofs);
	}
	bool deserialize(const char* filename)
	{
		if (!filename)
		{
			return false;
		}

		std::ifstream ifs(filename, std::ios::binary);
		if (!ifs.is_open())
		{
			return false;
		}

		deserialize(ifs);
	}
};
int main()
{
	float firstGrades[4] = { 5, 4.7, 6, 3 };
	float secondGrades[6] = { 2, 4.3, 6, 5.5, 5.2, 5.3 };
	Student students[2] = { {"Student1", "Family1", firstGrades, 4, "1111111111"},  {"Student2", "Family2", secondGrades, 6, "2222222222"} };
	Subject subject(students, 2, { "Ivan", "Petrov", Department::ComputerScience });

	subject.serialize("subject.dat");

	Subject deserialized;
	deserialized.deserialize("subject.dat");
}