#pragma once
#include "MyString.h"

enum class Major
{
	I,IS,CS,SI,M,AM,S,MI
};
class Student
{
	MyString name;
	MyString fn;
	Major major;
public:
	Student() = default;
	Student(const MyString& name, const MyString& fn, Major major);

	const MyString& getName() const;
	const MyString& getFN() const;
	Major getMajor() const;

	void setName(const MyString& name);
	void setFN(const MyString& fn);
	void setMajor(Major major);
};
std::ostream& operator<<(std::ostream& os, const Student& st);