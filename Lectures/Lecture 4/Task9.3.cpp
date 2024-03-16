#include <iostream>
#include <fstream>
#pragma warning (disable: 4996)

constexpr size_t MAX_WORD_LENGTH = 100;
constexpr size_t MAX_DEFINITION_LENGTH = 500;
constexpr size_t MAX_PAIRS_COUNT = 500;

struct Pair
{
	char word[MAX_WORD_LENGTH + 1];
	char definition[MAX_DEFINITION_LENGTH + 1];
};
class Dictionary
{
	Pair pairs[MAX_PAIRS_COUNT];
	size_t pairsCount;
	int indexOf(const char* word) const
	{
		if (!word)
		{
			return -1;
		}
		for (size_t i = 0; i < pairsCount; i++)
		{
			if (strcmp(word, pairs[i].word) == 0)
			{
				return i;
			}
		}
		return -1;
	}
	bool contains(const Pair& pair) const
	{
		return indexOf(pair.word) > -1;
	}
	void orderByName()
	{
		for (size_t i = 0; i < pairsCount; i++)
		{
			int minIndex = i;
			for (size_t j = i + 1; j < pairsCount; j++)
			{
				if (strcmp(pairs[j].word, pairs[minIndex].word) < 0)
				{
					minIndex = j;
				}
			}
			if (minIndex != i)
			{
				std::swap(pairs[minIndex], pairs[i]);
			}
		}
	}
public:
	Dictionary()
	{
		pairsCount = 0;
	}
	Dictionary(const Pair* pairs, size_t pairsCount)
	{
		if (!pairs)
		{
			return;
		}

		for (size_t i = 0; i < pairsCount; i++)
		{
			this->pairs[i] = pairs[i];
		}
		this->pairsCount = pairsCount;
	}
	void print() const
	{
		for (size_t i = 0; i < pairsCount; i++)
		{
			std::cout << pairs[i].word << ": " << pairs[i].definition << std::endl;
		}
	}
	bool addPair(const Pair& pair)
	{
		if (pairsCount + 1 > MAX_PAIRS_COUNT || contains(pair))
		{
			return false;
		}

		pairs[pairsCount++] = pair;
		return true;
	}
	bool remove(const char* word)
	{
		if (!word)
		{
			return false;
		}

		int pairIndex = indexOf(word);
		if (pairIndex == -1)
		{
			return false;
		}

		for (size_t i = pairIndex; i < pairsCount - 1; i++)
		{
			pairs[i] = pairs[i + 1];
		}
		pairsCount--;

		return true;
	}
	const char* getDefinition(const char* word) const
	{
		if (!word)
		{
			return nullptr;
		}

		int pairIndex = indexOf(word);
		if (pairIndex == -1)
		{
			return nullptr;
		}

		return pairs[pairIndex].definition;
	}
	void printSortedByWord() const
	{
		Dictionary* temp = new Dictionary(this->pairs, this->pairsCount);
		temp->orderByName();

		temp->print();
		delete temp;
	}
	Dictionary* operator+(const Dictionary& other) const
	{
		Dictionary* result = new Dictionary(this->pairs, this->pairsCount);
		for (size_t i = 0; i < other.pairsCount; i++)
		{
			if (!result->contains(other.pairs[i]))
			{
				if (!result->addPair(other.pairs[i]))
				{
					break;
				}
			}
			else
			{
				int pairIndex = indexOf(other.pairs[i].word);
				strcat(result->pairs[pairIndex].definition, "; ");
				strcat(result->pairs[pairIndex].definition, other.pairs[i].definition);
			}
		}

		return result;
	}
};
int main()
{
	Pair pairs1[] = { {"B", "gosho"}, {"D", "pesho"}, {"A", "Ivan"}, {"E", "Test"}, {"C", "Meaing"} };
	Dictionary* dict1 = new Dictionary(pairs1, 5);
	dict1->addPair({ "TestWord", "TestMeaning" });
	dict1->remove("A");
	dict1->remove("adasdfgsdg");

	Pair pairs2[] = { {"D", "pesho"}, {"Z", "Testqw"},  {"S", "sx"}, {"Y", "dffff"}, {"C", "adlksnansd"} };
	Dictionary* dict2 = new Dictionary(pairs2, 5);

	dict1->print();
	std::cout << std::endl;
	dict2->print();
	std::cout << std::endl;

	dict1->printSortedByWord();
	std::cout << std::endl;
	dict2->printSortedByWord();
	std::cout << std::endl;

	Dictionary* dictUnion = *dict1 + *dict2;
	dictUnion->printSortedByWord();

	delete dict1;
	delete dict2;
	delete dictUnion;
}