#include <iostream>
#include <cmath>
#include "MyString.h"
#include "HelperFunctions.h"
#pragma warning (disable: 4996)

void MyString::copyFrom(const MyString& other)
{
	this->data = new char[other.capacity] {0};
	strcpy(this->data, other.data);
	this->capacity = other.capacity;
	this->length = other.length;
}

void MyString::free()
{
	delete[] data;
	data = nullptr;
	length = 0;
}

void MyString::resize(unsigned newCapacity)
{
	char* temp = new char[newCapacity] {0};
	capacity = newCapacity;
	strcpy(temp, this->data);
	delete[] this->data;
	this->data = temp;
}

MyString::MyString() : MyString("") {}

MyString::MyString(const char* data)
{
	if (!data)
	{
		return;
	}
	this->length = strlen(data);
	this->capacity = getNextPowerOfTwo(this->length);
	this->data = new char[this->capacity] {0};
	strcpy(this->data, data);
}

MyString::MyString(const MyString& other)
{
	copyFrom(other);
}

MyString::~MyString()
{
	free();
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

char MyString::at(int index) const
{
	if (index < 0 || index >= length)
	{
		return 0;
	}
	return data[index];
}

char MyString::front() const
{
	if (this->empty())
	{
		return 0;
	}
	return data[0];
}

char MyString::back() const
{
	if (this->empty())
	{
		return 0;
	}
	return data[length - 1];
}

const char* MyString::str() const
{
	return data;
}

size_t MyString::getLength() const
{
	return length;
}

size_t MyString::getCapacity() const
{
	return capacity;
}

bool MyString::empty() const
{
	return length == 0;
}

MyString& MyString::append(char c)
{
	if (length + 1 >= capacity)
	{
		resize(capacity * 2);
	}
	this->data[length++] = c;
	return *this;
}

MyString& MyString::append(const MyString& str)
{
	//strcat() can also be used here
	for (size_t i = 0; i < str.length; i++)
	{
		append(str.at(i));
	}
	return *this;
}

void MyString::clear()
{
	for (size_t i = 0; i < length; i++)
	{
		data[i] = 0;
	}
	this->length = 0;
}

bool MyString::equals(const MyString& str) const
{
	return cmp(*this, str) == 0;
}

int MyString::find(char c) const
{
	for (size_t i = 0; i < length; i++)
	{
		if (data[i] == c)
		{
			return i;
		}
	}
	return -1;
}

void MyString::shrinkToFit()
{
	resize(length + 1);
}

void swap(MyString& first, MyString& second)
{
	MyString temp = first;
	first = second;
	second = temp;
}

int MyString::find(const MyString& str) const
{
	int startIndex = -1;
	int count = 0;
	for (size_t i = 0; i < length && count < str.length; i++)
	{
		if (data[i] == str.data[count])
		{
			if (startIndex == -1)
			{
				startIndex = i;
			}
			count++;
		}
		else if (count > 0)
		{
			i -= count - 1;
			count = 0;
			startIndex = -1;
		}
	}
	return count == str.length ? startIndex : -1;
}

bool MyString::contains(char c) const
{
	return find(c) >= 0;
}

bool MyString::contains(const MyString& str) const
{
	return find(str) >= 0;
}

int cmp(const MyString& first, const MyString& second)
{
	size_t longerLength = first.getLength() >= second.getLength() ? first.getLength() : second.getLength();

	for (size_t i = 0; i < longerLength; i++)
	{
		int diff = first.at(i) - second.at(i);
		if (diff != 0)
		{
			return diff / abs(diff);
		}
	}
	return 0;
}
