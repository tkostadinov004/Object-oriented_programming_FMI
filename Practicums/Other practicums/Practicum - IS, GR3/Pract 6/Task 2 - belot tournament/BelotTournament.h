#pragma once
#include "Team.h"

class BelotTournament
{
	Team* teams = nullptr;
	size_t teamsCount = 0;
	void copyFrom(const BelotTournament& other);
	void free();
public:
	BelotTournament();
	BelotTournament(size_t teamsCount);
	BelotTournament(const BelotTournament& other);
	~BelotTournament();
	BelotTournament& operator=(const BelotTournament& other);

	size_t getTeamsCount() const;
	void start() const;
};