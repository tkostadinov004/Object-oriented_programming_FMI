#include <iostream>
#include <fstream>
#pragma warning (disable: 4996)

constexpr size_t MAX_NAME_LENGTH = 50;
constexpr unsigned SPEED_OF_LIGHT = 299792; //km/s

struct Planet
{
	char name[MAX_NAME_LENGTH];
	double mass, diameter, distanceFromSun;
};
double secondsNeededForLightToReachPlanet(const Planet& planet)
{
	return planet.distanceFromSun / SPEED_OF_LIGHT;
}
void printPlanet(const Planet& planet)
{
	std::cout << "Name: " << planet.name << std::endl;
	std::cout << "Distance from the Sun: " << planet.distanceFromSun << " km." << std::endl;
	std::cout << "Diameter: " << planet.diameter << std::endl;
	std::cout << "Mass: " << planet.mass << std::endl;
	std::cout << "Seconds needed for light to reach the planet: " << secondsNeededForLightToReachPlanet(planet) << " seconds" << std::endl << std::endl;
}
void printPlanets(const Planet* arr, size_t size)
{
	if (!arr)
	{
		return;
	}

	for (size_t i = 0; i < size; i++)
	{
		printPlanet(arr[i]);
	}
}

unsigned getCharOccurrences(std::ifstream& file, char c)
{
	unsigned count = 0;
	while (true)
	{
		char current = file.get();
		if (file.eof())
		{
			break;
		}
		if (current == c)
		{
			count++;
		}
	}
	return count;
}
unsigned getLinesCount(std::ifstream& file)
{
	return getCharOccurrences(file, '\n') + 1;
}
void serializePlanet(std::ofstream& ofs, const Planet& planet)
{
	ofs << planet.name << " " << planet.mass << " " << planet.diameter << " " << planet.distanceFromSun << std::endl;
}
void serializeArray(const char* dest, const Planet* arr, size_t size)
{
	if (!dest || !arr)
	{
		return;
	}
	std::ofstream ofs(dest);
	if (!ofs.is_open())
	{
		return;
	}

	for (size_t i = 0; i < size; i++)
	{
		serializePlanet(ofs, arr[i]);
	}
}
Planet deserializePlanet(std::ifstream& ifs)
{
	Planet planet{};

	char nameBuffer[MAX_NAME_LENGTH];
	ifs >> nameBuffer;
	strcpy(planet.name, nameBuffer);

	ifs >> planet.mass >> planet.diameter >> planet.distanceFromSun;
	ifs.ignore();

	return planet;
}
Planet* deserializeArray(const char* src, size_t& size)
{
	if (!src)
	{
		return nullptr;
	}

	std::ifstream ifs(src);
	if (!ifs.is_open())
	{
		return nullptr;
	}

	size = getLinesCount(ifs) - 1;
	ifs.clear();
	ifs.seekg(0);

	Planet* arr = new Planet[size];
	for (size_t i = 0; i < size; i++)
	{
		arr[i] = deserializePlanet(ifs);
	}

	return arr;
}
int main()
{
	Planet planets[] = { {"Mercury", 3285000, 4880, 580000 }, {"Venus", 500000.2, 6000.1, 900000} };
	serializeArray("planets.txt", planets, 2);

	size_t size = 0;
	Planet * result = deserializeArray("planets.txt", size);
	printPlanets(result, size);

	delete[] result;
}