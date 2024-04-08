#pragma once
#include "NVector.h"

class CoordinateSystem
{
	NVector firstBasis;
	NVector secondBasis;
public:
	CoordinateSystem() = default;
	CoordinateSystem(const NVector& firstBasis, const NVector& secondBasis);

	const NVector& getFirstBasis() const;
	const NVector& getSecondBasis() const;

	void setFirstBasis(const NVector& firstBasis);
	void setSecondBasis(const NVector& secondBasis);

	NVector getVectorByCoordinates(double x, double y) const;
	NVector getCoordinatesByVector(double x, double y) const;

};