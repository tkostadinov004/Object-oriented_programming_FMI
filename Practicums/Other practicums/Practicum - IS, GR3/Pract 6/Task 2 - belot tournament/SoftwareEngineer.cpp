#include <iostream>
#include "SoftwareEngineer.h"
#pragma warning (disable: 4996)

void SoftwareEngineer::copyFrom(const SoftwareEngineer& other)
{
    this->name = new char[strlen(other.name) + 1];
    strcpy(this->name, other.name);

    this->position = new char[strlen(other.position) + 1];
    strcpy(this->position, other.position);

    this->salary = other.salary;
}

void SoftwareEngineer::free()
{
    delete[] name;
    delete[] position;

    name = nullptr;
    position = nullptr;
}

SoftwareEngineer::SoftwareEngineer() = default;

SoftwareEngineer::SoftwareEngineer(const char* name, const char* position, unsigned salary)
{
    setName(name);
    setPosition(position);
    setSalary(salary);
}

SoftwareEngineer::SoftwareEngineer(const SoftwareEngineer& other)
{
    copyFrom(other);
}

SoftwareEngineer::~SoftwareEngineer()
{
    free();
}

SoftwareEngineer& SoftwareEngineer::operator=(const SoftwareEngineer& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

const char* SoftwareEngineer::getName() const
{
    return name;
}

const char* SoftwareEngineer::getPosition() const
{
    return position;
}

unsigned SoftwareEngineer::getSalary() const
{
    return salary;
}

void SoftwareEngineer::setName(const char* name)
{
    if (!name)
    {
        return;
    }

    if (this->name == name)
    {
        return;
    }
    delete[] this->name;
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

void SoftwareEngineer::setPosition(const char* position)
{
    if (!position)
    {
        return;
    }

    if (this->position == position)
    {
        return;
    }
    delete[] this->position;
    this->position = new char[strlen(position) + 1];
    strcpy(this->position, position);
}

void SoftwareEngineer::setSalary(unsigned salary)
{
    this->salary = salary;
}
