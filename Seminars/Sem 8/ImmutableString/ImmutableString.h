#pragma once
#include "StringPool.h"
class ImmutableString
{
	static StringPool _pool;

	const char* _data;
	void copyFrom(const ImmutableString& other);
	void free();
public:
	ImmutableString(const char* str);
	ImmutableString(const ImmutableString& other);
	ImmutableString& operator=(const ImmutableString& other);
	~ImmutableString();

	char operator[](int index) const;
	const char* c_str() const;
	size_t length() const;
};