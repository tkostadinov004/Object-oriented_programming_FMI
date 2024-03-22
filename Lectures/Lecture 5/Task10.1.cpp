#include <iostream>
#include <fstream>
#pragma warning (disable: 4996)

constexpr size_t WORD_LENGTH = 20;
class Word
{
	char word[WORD_LENGTH + 1]{ 0 };
	size_t count = 0;
public:
	Word() = default;
	Word(const char* word)
	{
		setWord(word);
	}
	Word(const Word& word)
	{
		this->count = word.count;
		strcpy(this->word, word.word);
	}
	const char* getWord() const
	{
		return word;
	}
	void setWord(const char* word)
	{
		if (!word)
		{
			return;
		}

		if (strlen(word) > WORD_LENGTH)
		{
			return;
		}
		this->count = strlen(word);
		strcpy(this->word, word);
	}
	char operator[](int index) const
	{
		if (index < 0 || index >= WORD_LENGTH)
		{
			return 0;
		}
		return word[index];
	}
	Word operator+(char c) const
	{
		Word result = *this;
		if (count + 1 < WORD_LENGTH)
		{
			result.word[result.count++] = c;
		}
		return result;
	}
	Word& operator+=(char c)
	{
		if (count + 1 < WORD_LENGTH)
		{
			this->word[this->count++] = c;
		}
		return *this;
	}
	bool operator<(const Word& other) const
	{
		return strcmp(this->word, other.word) < 0;
	}
	bool operator==(const Word& other) const
	{
		return strcmp(this->word, other.word) == 0;
	}
};
std::ostream& operator<<(std::ostream& os, const Word& word)
{
	os << word.getWord();
	return os;
}
int main()
{
	Word w1("constructor");
	std::cout << w1[-1] << std::endl; // corner case - returns '\0' 
	std::cout << w1[11] << std::endl; // corner case - returns '\0' 
	std::cout << w1[0] << std::endl;

	std::cout << w1 + 's' + '_' + 'c' + '+' + '+' << std::endl;
	(w1 += 'i') += 's';
	std::cout << w1 << std::endl;

	std::cout << (w1 < "dsa") << std::endl;
	std::cout << (w1 == "constructor") << std::endl;
	std::cout << (w1 == "constructoris") << std::endl;

	Word w2("thewordwithlength20");
	std::cout << w2 + 'a' << std::endl; //shouldn't add to word
}