#pragma once
#include <iostream>
#include "MyString.h"
#include "HelperFunctions.h"

class StringSet
{
	MyString* data = nullptr;
	size_t size = 0;
	size_t capacity = 8;
	int getInsertionIndex(const MyString& str) const;
	int findStr(const MyString& str) const;
	void resize(size_t newCapacity);
	void copyFrom(const StringSet& other);
	void free();
public:
	StringSet();
	StringSet(const StringSet& other);
	~StringSet();
	StringSet& operator=(const StringSet& other);

	StringSet& operator+=(const StringSet& rhs);
	StringSet& operator-=(const StringSet& rhs);
	StringSet& operator*=(const MyString& str);
	StringSet& operator/=(const MyString& str);
	bool operator[](const MyString& str) const;
	friend std::ostream& operator<<(std::ostream& os, const StringSet& set);
};
StringSet operator+(const StringSet& lhs, const StringSet& rhs);
StringSet operator-(const StringSet& lhs, const StringSet& rhs);
std::istream& operator>>(std::istream& is, StringSet& set);
const MyString& operator>>(const MyString& str, StringSet& set);