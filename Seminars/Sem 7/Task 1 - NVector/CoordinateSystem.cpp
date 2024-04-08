#include "CoordinateSystem.h"

CoordinateSystem::CoordinateSystem(const NVector& firstBasis, const NVector& secondBasis)
{
    if (firstBasis.getLength() != secondBasis.getLength())
    {
        throw "The dimensions of the two vectors are not equal!";
    }

    setFirstBasis(firstBasis);
    setSecondBasis(secondBasis);
}

const NVector& CoordinateSystem::getFirstBasis() const
{
    return firstBasis;
}

const NVector& CoordinateSystem::getSecondBasis() const
{
    return secondBasis;
}

void CoordinateSystem::setFirstBasis(const NVector& firstBasis)
{
    this->firstBasis = firstBasis;
}

void CoordinateSystem::setSecondBasis(const NVector& secondBasis)
{
    this->secondBasis = secondBasis;
}

NVector CoordinateSystem::getVectorByCoordinates(double x, double y) const
{
    NVector result(2);
    for (size_t i = 0; i < result.getLength(); i++)
    {
        result[i] = x * firstBasis[i] + y * secondBasis[i];
    }
    return result;
}

NVector CoordinateSystem::getCoordinatesByVector(double x, double y) const
{
    double mult2 = ((-x) * firstBasis[1] + y * firstBasis[0]) / ((-secondBasis[0]) * firstBasis[1] + firstBasis[0] * secondBasis[1]);
    double mult1 = (x - mult2 * secondBasis[0]) / firstBasis[0];

    NVector result(2);
    result[0] = mult1;
    result[1] = mult2;
    return result;
}
