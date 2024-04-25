#pragma once
class StringPool
{
	struct StringRecord
	{
		char* data = nullptr;
		size_t occurrencesCount = 0;
	};
	StringRecord* _records = nullptr;
	size_t _size = 0;
	size_t _capacity = 8;
	int getStringIndex(const char* str) const;
	void addRecord(const char* str);
	void removeRecord(int index);
	void resize(size_t newCapacity);
	void free();
public:
	StringPool();
	const char* getAllocatedString(const char* str);
	void freeString(const char* str);
};