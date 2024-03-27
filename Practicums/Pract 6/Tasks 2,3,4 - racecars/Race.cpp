#include <iostream>
#include "Race.h"

void Race::copyFrom(const Race& other)
{
    setTrack(other.track);

    this->cars = other.cars;
    this->carsCount = other.carsCount;
}

Car* Race::orderCars() const
{
    Car* ordered = new Car[carsCount];
    for (size_t i = 0; i < carsCount; i++)
    {
        ordered[i] = cars[i];
    }

    for (size_t i = 0; i < carsCount; i++)
    {
        int minIndex = i;
        for (size_t j = i + 1; j < carsCount; j++)
        {
            if (calculateCarCoefficient(ordered[j]) < calculateCarCoefficient(ordered[minIndex]))
            {
                minIndex = j;
            }
        }
        if (minIndex != i)
        {
            std::swap(ordered[minIndex], ordered[i]);
        }
    }
    return ordered;
}

float Race::calculateCarCoefficient(const Car& car) const
{
    float slowCoeff = track->getSlowCorners() * car.getAcceleration() * (car.getDrivetrain() == Drivetrain::FourWheel ? 1.2 : 1);
    float fastCoeff = track->getFastCorners() * car.getHandling() * (car.getDrivetrain() == Drivetrain::FrontWheel ? 0.9 : 1);
    float lengthCoeff = (track->getStraightLength() / 100.0) * car.getTopSpeed();
    return slowCoeff + fastCoeff + lengthCoeff;
}

Race::Race() : track(nullptr), cars(nullptr), carsCount(0) {}

Race::Race(Track* track, Car* cars, size_t carsCount)
{
    setTrack(track);

    this->cars = cars;
    this->carsCount = carsCount;
}

const Track& Race::getTrack() const
{
    if (!track)
    {
        return {};
    }
    return *track;
}

void Race::setTrack(Track* track)
{
    this->track = track;
}

const Car* Race::getCars() const
{
    return cars;
}

size_t Race::getCarsCount() const
{
    return carsCount;
}

void Race::classify() const
{
    Car* ordered = orderCars();
    for (size_t i = 0; i < carsCount; i++)
    {
        std::cout << i + 1 << ": ";
        ordered[i].print();
        std::cout << std::endl;
    }
    delete[] ordered;
}
