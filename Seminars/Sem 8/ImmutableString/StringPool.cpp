#include "StringPool.h"
#include <string.h>
#pragma warning (disable: 4996)

int StringPool::getStringIndex(const char* str) const
{
	if (!str)
	{
		return -1;
	}

	for (size_t i = 0; i < _size; i++)
	{
		if (strcmp(str, _records[i].data) == 0)
		{
			return i;
		}
	}
    return -1;
}

void StringPool::addRecord(const char* str)
{
	if (!str)
	{
		return;
	}
	if (_size + 1 > _capacity)
	{
		resize(_capacity * 2);
	}

	_records[_size].data = new char[strlen(str) + 1];
	strcpy(_records[_size].data, str);
	_size++;
}

void StringPool::removeRecord(int index)
{
	delete[] _records[index].data;
	for (size_t i = index; i < _size - 1; i++)
	{
		_records[i] = _records[i + 1];
	}
	_size--;
}

void StringPool::resize(size_t newCapacity)
{
	StringRecord* temp = _records;
	_records = new StringRecord[newCapacity];
	for (size_t i = 0; i < _size; i++)
	{
		_records[i] = temp[i];
	}
	_capacity = newCapacity;
}

void StringPool::free()
{
	delete[] _records;
}

StringPool::StringPool()
{
	_records = new StringRecord[_capacity];
}

const char* StringPool::getAllocatedString(const char* str)
{
	int index = getStringIndex(str);
	if (index == -1)
	{
		addRecord(str);
		index = _size - 1;
	}
	_records[index].occurrencesCount++;
	return _records[index].data;
}

void StringPool::freeString(const char* str)
{
	int index = getStringIndex(str);
	if (index == -1)
	{
		return;
	}

	_records[index].occurrencesCount--;
	if (_records[index].occurrencesCount == 0)
	{
		removeRecord(index);
	}
}