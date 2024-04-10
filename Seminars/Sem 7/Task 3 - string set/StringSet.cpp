#include "StringSet.h"

int StringSet::getInsertionIndex(const MyString& str) const
{
	if (size == 0)
	{
		return 0;
	}

	int left = 0;
	int right = size - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		int res = cmp(str, data[mid]);
		if (res < 0)
		{
			right = mid - 1;
		}
		else if (res > 0)
		{
			left = mid + 1;
		}
		else
		{
			return mid + 1;
		}
	}
	return right + 1;
}

int StringSet::findStr(const MyString& str) const
{
	int left = 0;
	int right = size - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		int res = cmp(str, data[mid]);
		if (res < 0)
		{
			right = mid - 1;
		}
		else if (res > 0)
		{
			left = mid + 1;
		}
		else
		{
			return mid;
		}
	}
	return -1;
}

void StringSet::resize(size_t newCapacity)
{
	MyString* temp = new MyString[newCapacity];
	for (size_t i = 0; i < this->size; i++)
	{
		temp[i] = this->data[i];
	}
	delete[] this->data;
	data = temp;
	this->capacity = newCapacity;
}

void StringSet::copyFrom(const StringSet& other)
{
	this->data = new MyString[other.capacity];
	for (size_t i = 0; i < other.size; i++)
	{
		this->data[i] = other.data[i];
	}
	this->size = other.size;
	this->capacity = other.capacity;
}

void StringSet::free()
{
	delete[] this->data;
	this->size = 0;
	this->data = nullptr;
}

StringSet::StringSet()
{
	data = new MyString[capacity];
}

StringSet::StringSet(const StringSet& other)
{
	copyFrom(other);
}

StringSet::~StringSet()
{
	free();
}

StringSet& StringSet::operator=(const StringSet& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

StringSet& StringSet::operator+=(const StringSet& rhs)
{
	for (size_t i = 0; i < rhs.size; i++)
	{
		*this *= rhs.data[i];
	}
	return *this;
}

StringSet& StringSet::operator-=(const StringSet& rhs)
{
	for (size_t i = 0; i < rhs.size; i++)
	{
		*this /= rhs.data[i];
	}
	return *this;
}

StringSet& StringSet::operator*=(const MyString& str)
{
	if ((*this)[str])
	{
		return *this;
	}

	if (size + 1 > capacity)
	{
		resize(capacity * 2);
	}

	int insertionIndex = getInsertionIndex(str);
	for (int i = size; i > insertionIndex; i--)
	{
		swap(data[i], data[i - 1]);
	}
	data[insertionIndex] = str;
	size++;
	return *this;
}

StringSet& StringSet::operator/=(const MyString& str)
{
	int index = findStr(str);
	if (index != -1)
	{
		for (size_t i = index; i < size - 1; i++)
		{
			data[i] = data[i + 1];
		}
		size--;
	}
	return *this;
}

bool StringSet::operator[](const MyString& str) const
{
	return findStr(str) != -1;
}

std::ostream& operator<<(std::ostream& os, const StringSet& set)
{
	os << "{";
	for (size_t i = 0; i < set.size; i++)
	{
		os << set.data[i].str();
		if (i < set.size - 1)
		{
			os << ", ";
		}
	}
	os << "}";
	return os;
}

std::istream& operator>>(std::istream& is, StringSet& set)
{
	char buffer[1024];
	is.getline(buffer, 1024);
	set *= buffer;
	return is;
}

const MyString& operator>>(const MyString& str, StringSet& set)
{
	set *= str;
	return str;
}

StringSet operator+(const StringSet& lhs, const StringSet& rhs)
{
	StringSet result(lhs);
	result += rhs;
	return result;
}

StringSet operator-(const StringSet& lhs, const StringSet& rhs)
{
	StringSet result(lhs);
	result -= rhs;
	return result;
}
