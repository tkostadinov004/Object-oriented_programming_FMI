#pragma once
#include "Track.h"
#include "Car.h"
class Race //aggregation example
{
	Track* track;
	Car* cars;
	size_t carsCount;
	void copyFrom(const Race& other);
	Car* orderCars() const;
	float calculateCarCoefficient(const Car& car) const;
public:
	Race();
	Race(Track* track, Car* cars, size_t carsCount);
	const Track& getTrack() const;
	void setTrack(Track* track);
	const Car* getCars() const;
	size_t getCarsCount() const;
	void classify() const;
};