#include <iostream>
#include <fstream>
#pragma warning (disable: 4996)

constexpr size_t TITLE_LENGTH = 64;
class Game
{
	char title[TITLE_LENGTH];
	bool isAvailable;
	float price;
public:
	Game(const char* title = "", float price = 0, bool isAvailable = true)
	{
		setPrice(price);
		setAvailability(isAvailable);

		if (!title || strlen(title) > TITLE_LENGTH - 1)
		{
			return;
		}
		strcpy(this->title, title);
	}
	const char* getTitle() const
	{
		return title;
	}
	void setTitle(const char* str)
	{
		if (!str || strlen(str) > TITLE_LENGTH - 1)
		{
			return;
		}

		strcpy(this->title, str);
	}
	bool getAvailability() const
	{
		return this->isAvailable;
	}
	void setAvailability(bool value)
	{
		this->isAvailable = value;
	}
	float getPrice() const
	{
		return this->price;
	}
	void setPrice(float value)
	{
		if (value < 0)
		{
			return;
		}
		this->price = value;
	}
	bool isFree() const
	{
		return price == 0;
	}
	void print() const
	{
		std::cout << "Title: " << this->title << ", Price: " << this->price << ", Is available: " << (this->isAvailable ? "Yes" : "No") << std::endl;
	}
};
struct GameCollection
{
	Game* games;
	size_t count;
	void copyFrom(const GameCollection& gameCollection)
	{
		this->count = gameCollection.count;

		this->games = new Game[gameCollection.count];
		for (size_t i = 0; i < gameCollection.count; i++)
		{
			this->games[i] = gameCollection.games[i];
		}
	}
	GameCollection(size_t count = 0)
	{
		this->count = count;
		this->games = new Game[count];
	}
	GameCollection(const GameCollection& gameCollection)
	{
		copyFrom(gameCollection);
	}
	~GameCollection()
	{
		delete[] games;
	}
	void print() const
	{
		for (size_t i = 0; i < this->count; i++)
		{
			this->games[i].print();
		}
		std::cout << std::endl;
	}
};
class GamePlatform
{
	GameCollection collection;
	size_t capacity;
	const char SERIALIZATION_SEPARATOR = '|';
	size_t countGamesBy(bool(*pred)(Game)) const
	{
		size_t count = 0;
		for (size_t i = 0; i < this->collection.count; i++)
		{
			if (pred(this->collection.games[i]))
			{
				count++;
			}
		}
		return count;
	}
	int indexOf(const Game& game)
	{
		for (size_t i = 0; i < this->collection.count; i++)
		{
			if (strcmp(game.getTitle(), this->collection.games[i].getTitle()) == 0)
			{
				return i;
			}
		}
		return -1;
	}
	const GameCollection filterGamesBy(bool(*pred)(Game)) const
	{
		GameCollection result(countGamesBy(pred));

		int index = 0;
		for (size_t i = 0; i < this->collection.count; i++)
		{
			if (pred(this->collection.games[i]))
			{
				result.games[index++] = this->collection.games[i];
			}
		}
		return result;
	}
	const GameCollection orderByPrice() const
	{
		GameCollection result(this->collection.count);

		bool* visited = new bool[this->collection.count] {false};

		for (size_t i = 0; i < this->collection.count; i++)
		{
			int minIndex = 0;
			int minValue = INT_MAX;
			for (size_t j = 0; j < this->collection.count; j++)
			{
				if (!visited[j] && this->collection.games[j].getPrice() < minValue)
				{
					minIndex = j;
					minValue = this->collection.games[minIndex].getPrice();
				}
			}
			result.games[i] = this->collection.games[minIndex];
			visited[minIndex] = true;
		}
		delete[] visited;
		return result;
	}
	bool serialize(std::ofstream& ofs) const
	{
		ofs << this->collection.count << " " << this->capacity << std::endl;
		for (size_t i = 0; i < this->collection.count; i++)
		{
			ofs << this->collection.games[i].getTitle() << SERIALIZATION_SEPARATOR << this->collection.games[i].getPrice() << SERIALIZATION_SEPARATOR << this->collection.games[i].getAvailability();
			if (i < this->collection.count - 1)
			{
				ofs << std::endl;
			}
		}
		return ofs.good();
	}
	bool deserialize(std::ifstream& ifs)
	{
		size_t gamesCount = 0;
		ifs >> gamesCount >> this->capacity;
		GameCollection currentCollection(gamesCount);
		ifs.ignore();

		for (size_t i = 0; i < gamesCount; i++)
		{
			Game currentGame{};

			char titleBuffer[TITLE_LENGTH];
			ifs.getline(titleBuffer, TITLE_LENGTH, SERIALIZATION_SEPARATOR);
			currentGame.setTitle(titleBuffer);

			float price = 0;
			ifs >> price;
			ifs.ignore();
			currentGame.setPrice(price);

			bool isAvailable = false;
			ifs >> isAvailable;
			ifs.ignore();
			currentGame.setAvailability(isAvailable);

			currentCollection.games[i] = currentGame;
		}
		this->collection.copyFrom(currentCollection);
		return ifs.eof();
	}
public:
	GamePlatform()
	{
		this->collection.games = nullptr;
		this->collection.count = 0;
		this->capacity = 0;
	}
	GamePlatform(size_t capacity) : GamePlatform()
	{
		this->capacity = capacity;
		this->collection.games = new Game[capacity];
	}
	GamePlatform(const GamePlatform& gamePlatform) : collection(gamePlatform.collection.count)
	{
		this->capacity = gamePlatform.capacity;

		for (size_t i = 0; i < gamePlatform.collection.count; i++)
		{
			this->collection.games[i] = gamePlatform.collection.games[i];
		}
	}
	bool addGame(const Game& game)
	{
		if (this->collection.count + 1 > this->capacity)
		{
			return false;
		}

		this->collection.games[this->collection.count++] = game;
		return true;
	}
	bool removeGame(const Game& game)
	{
		int index = this->indexOf(game);
		if (index < 0)
		{
			return false;
		}

		for (size_t i = index; i < this->collection.count - 1; i++)
		{
			this->collection.games[i] = this->collection.games[i + 1];
		}
		this->collection.count--;
		return true;
	}
	Game getGameByIndex(int index) const
	{
		if (index < 0 || index >= this->collection.count)
		{
			return {};
		}

		return this->collection.games[index];
	}
	const GameCollection getAllGames() const
	{
		return this->filterGamesBy([](Game g) {return true;});
	}
	const GameCollection getAllFreeGames() const
	{
		return this->filterGamesBy([](Game g) {return g.getPrice() == 0;});
	}
	const Game getCheapestGame() const
	{
		const GameCollection sortedGames = this->orderByPrice();
		Game cheapest = sortedGames.games[0];

		return cheapest;
	}
	const Game getMostExpensiveGame() const
	{
		const GameCollection sortedGames = this->orderByPrice();
		Game mostExpensive = sortedGames.games[this->collection.count - 1];

		return mostExpensive;
	}
	bool serialize(const char* filename) const
	{
		if (!filename)
		{
			return false;
		}

		std::ofstream ofs(filename);
		if (!ofs.is_open())
		{
			return false; 
		}

		return this->serialize(ofs);
	}
	bool deserialize(const char* filename)
	{
		if (!filename)
		{
			return false;
		}

		std::ifstream ifs(filename);
		if (!ifs.is_open())
		{
			return false;
		}

		return this->deserialize(ifs);
	}
	void printGames() const
	{
		this->collection.print();
	}
};
int main()
{
	GamePlatform platform(5);
	platform.addGame({ "Far Cry 5", 40, true });
	platform.addGame({ "CS:GO", 0, true });
	platform.addGame({ "Europa Universalis", 60.99, false });
	platform.addGame({ "Assassin's Creed: Rogue", 30, true });
	platform.addGame({ "Madden NFL", 20, true });
	platform.addGame({ "NBA 2K24", 50, true }); // exceeds capacity: not added
	platform.printGames();

	Game ac = platform.getGameByIndex(3);
	ac.print();

	std::cout << platform.removeGame(ac) << std::endl;
	std::cout << platform.removeGame({"ashdhas"}) << std::endl; // not removing game

	GameCollection allGames = platform.getAllGames();
	std::cout << std::endl;
	allGames.print();

	GameCollection freeGames = platform.getAllFreeGames();
	freeGames.print();

	Game mostExpensive = platform.getMostExpensiveGame();
	Game cheapest = platform.getCheapestGame();

	mostExpensive.print();
	cheapest.print();

	std::cout << platform.serialize("games.txt") << std::endl;

	GamePlatform deserialized;
	if (deserialized.deserialize("games.txt"))
	{
		deserialized.printGames();
	}
}