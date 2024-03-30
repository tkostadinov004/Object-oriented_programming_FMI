#pragma once

class Subject
{
	char* name = nullptr;
	unsigned* grades = nullptr;
	size_t gradesCount = 0;
	void copyFrom(const Subject& other);
	void free();
public:
	Subject();
	Subject(const char* name, const unsigned* grades, size_t gradesCount);
	Subject(const Subject& other);
	~Subject();
	Subject& operator=(const Subject& other);

	const char* getName() const;
	const unsigned* getGrades() const;
	size_t getGradesCount() const;
	unsigned getAverageGrade() const;

	void setName(const char* name);
	void setGrades(const unsigned* grades, size_t gradesCount);

	void serializeSelf(std::ofstream& ofs);
	void deserializeSelf(std::ifstream& ifs);
};