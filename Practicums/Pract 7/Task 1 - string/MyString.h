#pragma once

class MyString
{
	char* data = nullptr;
	size_t length = 0;
	size_t capacity = 1;
	void copyFrom(const MyString& other);
	void free();
	void resize(unsigned newCapacity);
public:
	MyString();
	MyString(const char* data);
	MyString(const MyString& other);
	~MyString();
	MyString& operator=(const MyString& other);
	char at(int index) const;
	char front() const;
	char back() const;
	const char* str() const;
	size_t getLength() const;
	size_t getCapacity() const;
	bool empty() const;
	MyString& append(char c);
	MyString& append(const MyString& str);
	void clear();
	bool equals(const MyString& str) const;
	int find(char c) const;
	void shrinkToFit();
	friend void swap(MyString& first, MyString& second);
	int find(const MyString& str) const;
	bool contains(char c) const;
	bool contains(const MyString& str) const;
};
int cmp(const MyString& first, const MyString& second);