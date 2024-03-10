#include <iostream>
using namespace std;

namespace Constants
{
	constexpr unsigned MIN_FACULTY_NUMBER = 10000;
	constexpr unsigned MAX_FACULTY_NUMBER = 99999;
	constexpr size_t MAX_YEAR_NAME_LENGTH = 15;
	constexpr size_t GROUP_CAPACITY = 20;
}
enum class Year
{
	Freshman,
	Sophomore,
	Junior,
	Senior
};
struct Student
{
	unsigned facultyNumber;
	Year year;
	float averageGrade = 2;
};
Year getYearByName(const char* name)
{
	if (strcmp(name, "Freshman") == 0)
	{
		return Year::Freshman;
	}
	else if (strcmp(name, "Sophomore") == 0)
	{
		return Year::Sophomore;
	}
	else if (strcmp(name, "Junior") == 0)
	{
		return Year::Junior;
	}
	else
	{
		return Year::Senior;
	}
}
void printYearName(Year year)
{
	switch (year)
	{
		case Year::Freshman:
			cout << "Freshman";
			break;
		case Year::Sophomore:
			cout << "Sophomore";
			break;
		case Year::Junior:
			cout << "Junior";
			break;
		case Year::Senior:
			cout << "Senior";
			break;
	}
}
void initStudent(Student& student)
{
	unsigned facultyNumber;
	cin >> facultyNumber;
	if (facultyNumber >= Constants::MIN_FACULTY_NUMBER && facultyNumber <= Constants::MAX_FACULTY_NUMBER)
	{
		student.facultyNumber = facultyNumber;
	}
	cin.ignore();

	char yearName[Constants::MAX_YEAR_NAME_LENGTH + 1];
	cin.getline(yearName, Constants::MAX_YEAR_NAME_LENGTH);
	student.year = getYearByName(yearName);

	float averageGrade;
	cin >> averageGrade;
	if (averageGrade >= 2 && averageGrade <= 6)
	{
		student.averageGrade = averageGrade;
	}
}
struct Group
{
	Student students[Constants::GROUP_CAPACITY];
	size_t studentsCount = 0;
	float averageGrade = 2;
};
float getAverageGrade(const Group& group)
{
	float sum = 0;
	for (size_t i = 0; i < group.studentsCount; i++)
	{
		sum += group.students[i].averageGrade;
	}
	return sum / group.studentsCount;
}
void initializeGroup(Group& group)
{
	cin >> group.studentsCount;
	for (size_t i = 0; i < group.studentsCount; i++)
	{
		initStudent(group.students[i]);
	}
	group.averageGrade = getAverageGrade(group);
}
size_t getScholarshipEligibilityCount(float minGrade, const Group& group)
{
	size_t count = 0;
	for (size_t i = 0; i < group.studentsCount; i++)
	{
		if (group.students[i].averageGrade >= minGrade)
		{
			count++;
		}
	}
	return count;
}
void getEligibleStudents(float minGrade, const Group& group, Group& eligibleStudents)
{
	for (size_t i = 0; i < group.studentsCount; i++)
	{
		if (group.students[i].averageGrade >= minGrade)
		{
			eligibleStudents.students[eligibleStudents.studentsCount++] = group.students[i];
		}
	}
}
void sortByAverageGrade(Group& group)
{
	for (size_t i = 0; i < group.studentsCount; i++)
	{
		int maxIndex = i;
		for (size_t j = i + 1; j < group.studentsCount; j++)
		{
			if (group.students[j].averageGrade > group.students[maxIndex].averageGrade)
			{
				maxIndex = j;
			}
		}
		if (maxIndex != i)
		{
			swap(group.students[maxIndex], group.students[i]);
		}
	}
}
void printStudent(const Student& student)
{
	cout << "Faculty number: " << student.facultyNumber << ", Year: ";
	printYearName(student.year);
	cout << ", Average grade: " << student.averageGrade << endl;
}
void printGroup(const Group& group)
{
	for (size_t i = 0; i < group.studentsCount; i++)
	{
		printStudent(group.students[i]);
	}
}
int main()
{
	constexpr float MIN_SCHOLARSHIP_GRADE = 4.5;

	Group group{ {{55555, Year::Freshman, 4.3}, {32458, Year::Junior, 5}, {85434, Year::Senior, 5.3} }, 3 };
	cout << getScholarshipEligibilityCount(MIN_SCHOLARSHIP_GRADE, group) << endl;

	Group eligibleStudents{};
	getEligibleStudents(MIN_SCHOLARSHIP_GRADE, group, eligibleStudents);

	sortByAverageGrade(eligibleStudents);
	printGroup(eligibleStudents);
}