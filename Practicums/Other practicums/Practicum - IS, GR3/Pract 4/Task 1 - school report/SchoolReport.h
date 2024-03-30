#pragma once
#include <fstream>
#include "Subject.h"

class SchoolReport
{
	Subject* subjects = nullptr;;
	size_t subjectsCount = 0;
	void copyFrom(const SchoolReport& other);
	void free();
	void serializeSelf(std::ofstream& ofs) const;
	void deserializeSelf(std::ifstream& ifs);
public:
	SchoolReport();
	SchoolReport(const Subject* subjects, size_t subjectsCount);
	SchoolReport(const SchoolReport& other);
	~SchoolReport();
	SchoolReport& operator=(const SchoolReport& other);

	const Subject* getSubjects() const;
	size_t getSubjectsCount() const;

	void setSubjects(const Subject* subjects, size_t subjectsCount);

	void serializeSelf(const char* dest) const;
	void deserializeSelf(const char* src);
	unsigned getAverageGrade() const;
};