#include <iostream>
#include "SchoolReport.h"

int main()
{
	unsigned grades[3] = { 2,3,4 };
	unsigned grades2[5] = { 4.5, 3, 6, 5, 5 };
	Subject subjects[2]{ Subject("Intro to Programming", grades, 3), Subject("OOP", grades2, 5)};
	SchoolReport report(subjects, 2);
	
	report.serializeSelf("result.dat");

	SchoolReport result;
	result.deserializeSelf("result.dat");

	for (size_t i = 0; i < 2; i++)
	{
		std::cout << (report.getSubjects()[i].getAverageGrade() == result.getSubjects()[i].getAverageGrade()) << std::endl;
	}
	std::cout << (report.getAverageGrade() == result.getAverageGrade());
}