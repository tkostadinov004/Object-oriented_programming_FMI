#include <iostream>
#include <fstream>
#pragma warning (disable: 4996)
using namespace std;

constexpr size_t MAX_PAIRS_COUNT = 25;

struct Pair
{
	unsigned x, y;
};
struct Relation
{
	Pair pairs[MAX_PAIRS_COUNT];
	size_t pairsCount = 0;
};
void deserializePair(std::ifstream& ifs, Pair& pair)
{
	ifs >> pair.x >> pair.y;
}
void deserializeRelation(std::ifstream& ifs, Relation& relation)
{
	while (!ifs.eof())
	{
		deserializePair(ifs, relation.pairs[relation.pairsCount++]);
	}
}
void deserializeRelation(const char* filename, Relation& relation)
{
	if (!filename)
	{
		return;
	}

	std::ifstream ifs(filename);
	if (!ifs.is_open())
	{
		return;
	}

	deserializeRelation(ifs, relation);
}
void addToRelation(const Pair& pair, Relation& rel)
{
	rel.pairs[rel.pairsCount++] = pair;
}
void serializeRelation(std::ofstream& ofs, const Relation& rel)
{
	for (int i = 0; i < rel.pairsCount; i++)
	{
		ofs << rel.pairs[i].x << " " << rel.pairs[i].y;
		if (i < rel.pairsCount - 1)
		{
			ofs << std::endl;
		}
	}
}
void serializeRelation(const char* dest, const Relation& rel)
{
	if (!dest)
	{
		return;
	}

	std::ofstream ofs(dest);
	if (!ofs.is_open())
	{
		return;
	}

	serializeRelation(ofs, rel);
}
int main()
{
	Relation relation {};
	deserializeRelation("rel.txt", relation);

	Pair pair = { 10, 100 };
	addToRelation(pair, relation);
	serializeRelation("rel.txt", relation);
}