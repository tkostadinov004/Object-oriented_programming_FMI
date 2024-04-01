#include <iostream>
#include "Car.h"
#pragma warning (disable : 4996)

int main()
{
	Wheel w(20, Material::Aluminium);
	Car c1("VVSA", "T", "C", { 100, 200, "VIN" }, &w, 20, 20, 20, Drivetrain::FourWheel, 2, 3, 4);
	Car c2 = c1;
	Car c3;
	c3 = c2;
}

Car::Car() = default;

Car::Car(const char* regNumber, const char* manufacturer, const char* model, const Engine& engine, Wheel* wheel, float cityConsumption, float outOfCityConsumption, float combinedConsumption, Drivetrain drivetrain, int acceleration, int topSpeed, int handling)
{
	setRegNumber(regNumber);
	setManufacturer(manufacturer);
	setModel(model);
	setEngine(engine);
	setWheel(wheel);
	setFuelConsumption(cityConsumption, outOfCityConsumption, combinedConsumption);
	setDrivetrain(drivetrain);
	setAcceleration(acceleration);
	setTopSpeed(topSpeed);
	setHandling(handling);
}

const char* Car::getRegNumber() const
{
	return regNumber;
}

void Car::setRegNumber(const char* regNumber)
{
	if (!regNumber)
	{
		return;
	}

	if (strlen(regNumber) > CAR_REGNUMBER_LENGTH)
	{
		return;
	}
	strcpy(this->regNumber, regNumber);
}

const char* Car::getManufacturer() const
{
	return manufacturer;
}

void Car::setManufacturer(const char* manufacturer)
{
	if (!manufacturer)
	{
		return;
	}

	if (strlen(manufacturer) > CAR_MANUFACTURER_LENGTH)
	{
		return;
	}
	strcpy(this->manufacturer, manufacturer);
}

const char* Car::getModel() const
{
	return model;
}

void Car::setModel(const char* model)
{
	if (!model)
	{
		return;
	}

	if (strlen(model) > CAR_MODEL_LENGTH)
	{
		return;
	}
	strcpy(this->model, model);
}

const float* Car::getFuelConsumption() const
{
	return fuelConsumption;
}

void Car::setFuelConsumption(float city, float outOfCity, float combined)
{
	if (city < 0 || outOfCity < 0 || combined < 0)
	{
		return;
	}
	fuelConsumption[0] = city;
	fuelConsumption[1] = outOfCity;
	fuelConsumption[2] = combined;
}

const Engine& Car::getEngine() const
{
	return engine;
}

void Car::setEngine(const Engine& engine)
{
	this->engine = engine;
}

const Wheel& Car::getWheel() const
{
	if (!wheel)
	{
		return {};
	}
	return *wheel;
}

void Car::setWheel(Wheel* wheel)
{
	this->wheel = wheel;
}

Drivetrain Car::getDrivetrain() const
{
	return drivetrain;
}

void Car::setDrivetrain(Drivetrain drivetrain)
{
	this->drivetrain = drivetrain;
}

int Car::getAcceleration() const
{
	return acceleration;
}

void Car::setAcceleration(int acceleration)
{
	if (acceleration < 0 || acceleration > 100)
	{
		return;
	}
	this->acceleration = acceleration;
}

int Car::getTopSpeed() const
{
	return topSpeed;
}

void Car::setTopSpeed(int topSpeed)
{
	if (topSpeed < 0 || topSpeed > 100)
	{
		return;
	}
	this->topSpeed = topSpeed;
}

int Car::getHandling() const
{
	return handling;
}

void Car::setHandling(int handling)
{
	if (handling < 0 || handling > 100)
	{
		return;
	}
	this->handling = handling;
}

bool Car::isFuelEfficient() const
{
	for (size_t i = 0; i < CAR_FUEL_CONSUMPTION_ARR_COUNT; i++)
	{
		if (fuelConsumption[i] > 6)
		{
			return false;
		}
	}
	return true;
}

bool Car::isMoreFuelEfficient(const Car& other) const
{
	for (size_t i = 0; i < CAR_FUEL_CONSUMPTION_ARR_COUNT; i++)
	{
		if (this->fuelConsumption[i] >= other.fuelConsumption[i])
		{
			return false;
		}
	}
	return true;
}

void Car::print() const
{
	std::cout << regNumber << ", " << manufacturer << ", " << model;
}
