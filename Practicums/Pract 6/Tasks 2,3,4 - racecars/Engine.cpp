#include <iostream>
#include "Engine.h"
#pragma warning (disable: 4996)

void Engine::copyFrom(const Engine& other)
{
    setPower(other.power);
    setDisplacement(other.displacement);
    setVIN(other.VIN);
}

Engine::Engine() : Engine(0, 0, "undefined") {}

Engine::Engine(int power, int displacement, const char* VIN)
{
    setPower(power);
    setDisplacement(displacement);
    setVIN(VIN);
}

Engine::Engine(const Engine& other)
{
    copyFrom(other);
}

Engine& Engine::operator=(const Engine& other)
{
    if (this != &other)
    {
        copyFrom(other);
    }
    return *this;
}

int Engine::getPower() const
{
    return power;
}

void Engine::setPower(int power)
{
    if (power < 0)
    {
        return;
    }
    this->power = power;
}

int Engine::getDisplacement() const
{
    return displacement;
}

void Engine::setDisplacement(int displacement)
{
    if (displacement < 0)
    {
        return;
    }
    this->displacement = displacement;
}

const char* Engine::getVIN() const
{
    return VIN;
}

void Engine::setVIN(const char* VIN)
{
    if (!VIN)
    {
        return;
    }

    if (strlen(VIN) != ENGINE_VIN_LENGTH)
    {
        return;
    }
    strcpy(this->VIN, VIN);
}
