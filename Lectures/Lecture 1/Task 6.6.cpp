#include <iostream>
using namespace std;
constexpr size_t MAX_NAME_LENGTH = 50;
constexpr unsigned SPEED_OF_LIGHT = 299792; //km/s

struct Planet
{
	char name[MAX_NAME_LENGTH];
	double distanceFromSun, diameter, mass;
};
Planet userInput()
{
	Planet planet{};
	cout << "Enter planet name: ";
	cin.ignore();
	cin.getline(planet.name, MAX_NAME_LENGTH);

	cout << "Enter the planet's distance from the Sun: ";
	cin >> planet.distanceFromSun;

	cout << "Enter the planet's diameter: ";
	cin >> planet.diameter;

	cout << "Enter the planet's mass: ";
	cin >> planet.mass;

	cout << endl;
	return planet;
}
double secondsNeededForLightToReachPlanet(const Planet& planet)
{
	return planet.distanceFromSun / SPEED_OF_LIGHT;
}
void printPlanet(const Planet& planet)
{
	cout << "Name: " << planet.name << endl;
	cout << "Distance from the Sun: " << planet.distanceFromSun << " km." << endl;
	cout << "Diameter: " << planet.diameter << endl;
	cout << "Mass: " << planet.mass << endl;
	cout << "Seconds needed for light to reach the planet: " << secondsNeededForLightToReachPlanet(planet) << " seconds" << endl << endl;
}
Planet* createPlanets(size_t size)
{
	Planet* planets = new Planet[size];
	for (size_t i = 0; i < size; i++)
	{
		planets[i] = userInput();
	}

	return planets;
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
int main()
{
	size_t n;
	cin >> n;

	Planet* planets = createPlanets(n);
	printPlanets(planets, n);

	delete[] planets;
}

