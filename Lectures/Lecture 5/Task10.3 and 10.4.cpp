#include <iostream>
#include <fstream>
#pragma warning (disable: 4996)

constexpr size_t WORD_LENGTH = 20;
struct HistoryEntry
{
private:
	int month = 1;
	char* url = nullptr;
public:
	HistoryEntry() = default;
	HistoryEntry(const char* url, int month = 1)
	{
		setUrl(url);
		setMonth(month);
	}
	~HistoryEntry()
	{
		clear();
	}
	int getMonth() const
	{
		return month;
	}
	void setMonth(int month)
	{
		if (month < 1 || month > 12)
		{
			return;
		}

		this->month = month;
	}
	const char* getUrl() const
	{
		return url;
	}
	void setUrl(const char* url)
	{
		if (!url)
		{
			strcpy(new char[1] {""}, this->url);
		}

		delete[] this->url;
		this->url = new char[strlen(url) + 1];
		strcpy(this->url, url);
	}
	void copyFrom(const HistoryEntry& other)
	{
		this->month = other.month;
		setUrl(other.url);
	}
	void print() const
	{
		std::cout << url << ": " << month << std::endl;
	}
	void clear()
	{
		delete[] url;
	}
};
class BrowserHistory
{
	HistoryEntry* entries = nullptr;
	size_t count = 0;
	size_t capacity = 0;
	void grow() 
	{
		if (capacity == 0)
		{
			capacity = 1;
		}

		HistoryEntry* temp = new HistoryEntry[capacity *= 2];
		for (size_t i = 0; i < count; i++)
		{
			temp[i].copyFrom(entries[i]);
		}
		delete[] entries;
		entries = temp;
	}
public:
	BrowserHistory() = default;
	BrowserHistory(size_t capacity)
	{
		this->capacity = capacity;
		this->entries = new HistoryEntry[capacity];
	}
	BrowserHistory(const BrowserHistory& other)
	{
		copyFrom(other);
	}
	~BrowserHistory()
	{
		delete[] entries;
	}
	void addWebsite(const HistoryEntry& entry)
	{
		if (count + 1 > capacity)
		{
			grow();
		}

		this->entries[this->count++].copyFrom(entry);
	}
	void print() const
	{
		for (size_t i = 0; i < this->count; i++)
		{
			this->entries[i].print();
		}
	}
	unsigned getCountByMonth(int month) const
	{
		unsigned count = 0;
		for (size_t i = 0; i < this->count; i++)
		{
			if (this->entries[i].getMonth() == month)
			{
				count++;
			}
		}
		return count;
	}
	unsigned getMostVisitedMonth() const
	{
		unsigned maxMonth = 1;
		unsigned maxCount = 0;
		for (size_t i = 1; i <= 12; i++)
		{
			unsigned currentCount = getCountByMonth(i);
			if (currentCount > maxCount)
			{
				maxMonth = i;
				maxCount = currentCount;
			}
		}
		return maxMonth;
	}
	void pop()
	{
		if (count == 0)
		{
			return;
		}

		--this->count;
	}
	void copyFrom(const BrowserHistory& other)
	{
		this->count = 0;
		this->capacity = other.capacity;

		delete[] this->entries;
		this->entries = new HistoryEntry[other.capacity];
		for (size_t i = 0; i < other.count; i++)
		{
			this->addWebsite(other.entries[i]);
		}
	}
	BrowserHistory operator+(const BrowserHistory& other)
	{
		BrowserHistory result(*this);
		return result += other;
	}
	BrowserHistory operator+(const HistoryEntry& other)
	{
		BrowserHistory result(*this);
		return result += other;
	}
	BrowserHistory& operator=(const BrowserHistory& other)
	{
		if (this != &other)
		{
			copyFrom(other);
		}
		return *this;
	}
	BrowserHistory& operator+=(const HistoryEntry& other)
	{
		this->addWebsite(other);
		return *this;
	}
	BrowserHistory& operator+=(const BrowserHistory& other)
	{
		for (size_t i = 0; i < other.count; i++)
		{
			this->addWebsite(other.entries[i]);
		}
		return *this;
	}
};
int main()
{
	BrowserHistory history(3);
	history.addWebsite({ "google.com", 3 });
	history = (history + HistoryEntry{ "youtube.com", 3 });
	history += { "instagram.com", 2 };

	history.print();

	std::cout << history.getCountByMonth(3) << std::endl;
	std::cout << history.getMostVisitedMonth() << std::endl;
	for (size_t i = 0; i < 3; i++)
	{
		history.pop();
		history.print();
		std::cout << std::endl;
	}
	history.pop(); //shouldn't remove
	history.print();


}