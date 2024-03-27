#pragma once
#include "Engine.h"
#include "Wheel.h"

constexpr size_t CAR_REGNUMBER_LENGTH = 8;
constexpr size_t CAR_MANUFACTURER_LENGTH = 20;
constexpr size_t CAR_MODEL_LENGTH = 20;
constexpr size_t CAR_FUEL_CONSUMPTION_ARR_COUNT = 3;
enum class Drivetrain
{
	Undefined,
	FrontWheel,
	RearWheel,
	FourWheel
};
class Car
{
	char regNumber[CAR_REGNUMBER_LENGTH + 1];
	char manufacturer[CAR_MANUFACTURER_LENGTH + 1];
	char model[CAR_MODEL_LENGTH + 1];
	float fuelConsumption[3];
	Engine engine;
	Wheel* wheel;
	Drivetrain drivetrain;
	int acceleration;
	int topSpeed;
	int handling;
	void copyFrom(const Car& other);
public:
	Car();
	Car(const char* regNumber, const char* manufacturer, const char* model, const Engine& engine, Wheel* wheel, float cityConsumption, float outOfCityConsumption, float combinedConsumption, Drivetrain drivetrain, int acceleration, int topSpeed, int handling);
	Car(const Car& other);
	Car& operator=(const Car& other);
	const char* getRegNumber() const;
	void setRegNumber(const char* regNumber);
	const char* getManufacturer() const;
	void setManufacturer(const char* manufacturer);
	const char* getModel() const;
	void setModel(const char* model);
	const float* getFuelConsumption() const;
	void setFuelConsumption(float city, float outOfCity, float combined);
	const Engine& getEngine() const;
	void setEngine(const Engine& engine);
	const Wheel& getWheel() const;
	void setWheel(Wheel* wheel);
	Drivetrain getDrivetrain() const;
	void setDrivetrain(Drivetrain drivetrain);
	int getAcceleration() const;
	void setAcceleration(int acceleration);
	int getTopSpeed() const;
	void setTopSpeed(int topSpeed);
	int getHandling() const;
	void setHandling(int handling);
	bool isFuelEfficient() const;
	bool isMoreFuelEfficient(const Car& other) const;
	void print() const;
};