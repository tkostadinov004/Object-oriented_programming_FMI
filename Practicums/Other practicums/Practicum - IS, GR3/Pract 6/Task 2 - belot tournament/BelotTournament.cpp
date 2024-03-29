#include "BelotTournament.h"

void BelotTournament::copyFrom(const BelotTournament& other)
{
    this->teamsCount = other.teamsCount;
    this->teams = new Team[other.teamsCount];
    for (size_t i = 0; i < other.teamsCount; i++)
    {
        this->teams[i] = other.teams[i];
    }
}

void BelotTournament::free()
{
    delete[] teams;
    teams = nullptr;
}

BelotTournament::BelotTournament() = default;

BelotTournament::BelotTournament(size_t teamsCount)
{
    this->teamsCount = teamsCount;
    this->teams = new Team[teamsCount];
}

BelotTournament::BelotTournament(const BelotTournament& other)
{
    copyFrom(other);
}

BelotTournament::~BelotTournament()
{
    free();
}

BelotTournament& BelotTournament::operator=(const BelotTournament& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

size_t BelotTournament::getTeamsCount() const
{
    return teamsCount;
}

void BelotTournament::start() const
{
    //TODO: Add belot gameplay logic
}
