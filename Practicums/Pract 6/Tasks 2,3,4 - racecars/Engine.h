#pragma once

constexpr size_t ENGINE_VIN_LENGTH = 17;
class Engine
{
	int power;
	int displacement;
	char VIN[ENGINE_VIN_LENGTH + 1];
	void copyFrom(const Engine& other);
public:
	Engine();
	Engine(int power, int displacement, const char* VIN);
	int getPower() const;
	void setPower(int power);
	int getDisplacement() const;
	void setDisplacement(int displacement);
	const char* getVIN() const;
	void setVIN(const char* VIN);
};