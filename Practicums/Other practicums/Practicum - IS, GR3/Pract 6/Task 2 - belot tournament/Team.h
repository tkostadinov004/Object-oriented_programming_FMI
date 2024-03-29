#pragma once
#include "SoftwareEngineer.h"
class Team
{
	SoftwareEngineer first;
	SoftwareEngineer second;
public:
	Team();
	Team(const SoftwareEngineer& first, const SoftwareEngineer& second);
	const SoftwareEngineer& getFirstPlayer() const;
	const SoftwareEngineer& getSecondPlayer() const;
};