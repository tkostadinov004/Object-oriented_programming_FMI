#include "Track.h"

Track::Track() : Track(0, 0, 0) {}

Track::Track(int slowCorners, int fastCorners, int straightLength)
{
    setSlowCorners(slowCorners);
    setFastCorners(fastCorners);
    setStraightLength(straightLength);
}

int Track::getSlowCorners() const
{
    return slowCorners;
}

void Track::setSlowCorners(int slowCorners)
{
    if (slowCorners < 0)
    {
        return;
    }
    this->slowCorners = slowCorners;
}

int Track::getFastCorners() const
{
    return fastCorners;
}

void Track::setFastCorners(int fastCorners)
{
    if (fastCorners < 0)
    {
        return;
    }
    this->fastCorners = fastCorners;
}

int Track::getStraightLength() const
{
    return straightLength;
}

void Track::setStraightLength(int straightLength)
{
    if (straightLength < 0)
    {
        return;
    }
    this->straightLength = straightLength;
}
