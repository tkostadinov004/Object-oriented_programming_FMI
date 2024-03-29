#include "Team.h"

Team::Team() = default; 
Team::Team(const SoftwareEngineer& first, const SoftwareEngineer& second)
{
    this->first = first;
    this->second = second;
}

const SoftwareEngineer& Team::getFirstPlayer() const
{
    return first;
}

const SoftwareEngineer& Team::getSecondPlayer() const
{
    return second;
}
