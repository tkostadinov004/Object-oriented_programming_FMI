#include <iostream>
#include <fstream>
#pragma warning (disable: 4996)
using namespace std;

namespace Constants
{
	constexpr size_t NAME_LENGTH = 63;
	constexpr size_t MAX_DISTRICTS_COUNT = 20;
	constexpr char SEPARATOR = '|';
}
struct City
{
	char name[Constants::NAME_LENGTH + 1];
	unsigned population = 0;
};
struct District
{
	City cities[Constants::MAX_DISTRICTS_COUNT];
	size_t citiesCount = 0;
};
void serializeCity(std::ofstream& ofs, const City& city)
{
	ofs << city.name << Constants::SEPARATOR << city.population;
}
void serializeDistrict(std::ofstream& ofs, const District& district)
{
	for (int i = 0; i < district.citiesCount; i++)
	{
		serializeCity(ofs, district.cities[i]);
		if (i < district.citiesCount - 1)
		{
			ofs << endl;
		}
	}
}
void serializeDistrict(const char* dest, const District& district)
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

	serializeDistrict(ofs, district);
}
void deserializeCity(std::ifstream& ifs, City& city)
{
	char nameBuffer[Constants::NAME_LENGTH];
	ifs.getline(nameBuffer, Constants::NAME_LENGTH, Constants::SEPARATOR);
	strcpy(city.name, nameBuffer);

	ifs >> city.population;
	ifs.ignore();
}
void deserializeDistrict(std::ifstream& ifs, District& district)
{
	while (!ifs.eof())
	{
		deserializeCity(ifs, district.cities[district.citiesCount++]);
	}
}
void deserializeDistrict(const char* filename, District& district)
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

	deserializeDistrict(ifs, district);
}
void sortByPopulation(District& district)
{
	for (size_t i = 0; i < district.citiesCount; i++)
	{
		int minIndex = i;
		for (size_t j = i + 1; j < district.citiesCount; j++)
		{
			if (district.cities[j].population < district.cities[minIndex].population)
			{
				minIndex = j;
			}
		}
		if (minIndex != i)
		{
			swap(district.cities[minIndex], district.cities[i]);
		}
	}
}
void printCity(const City& city)
{
	cout << "Name: " << city.name << ", Population: " << city.population << " people" << endl;
}
void printDistrict(const District& district)
{
	for (size_t i = 0; i < district.citiesCount; i++)
	{
		printCity(district.cities[i]);
	}
}
int main()
{
	/*District district{ {{"Sofia", 1500000}, {"Plovdiv", 500000}, {"Veliko Tarnovo", 60000}, {"Ruse", 200000}, {"Varna", 300000}}, 5 };
	serializeDistrict("cities.txt", district);*/

	District district{};
	deserializeDistrict("cities.txt", district);
	sortByPopulation(district);

	printDistrict(district);
}