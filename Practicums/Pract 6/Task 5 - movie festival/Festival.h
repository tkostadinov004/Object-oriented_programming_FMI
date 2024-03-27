#pragma once
#include "Projection.h"

constexpr size_t FESTIVAL_NAME_LENGTH = 30;
class Festival
{
	char name[FESTIVAL_NAME_LENGTH + 1];
	Projection* projections;
	size_t projectionsCount;
	void copyFrom(const Festival& other);
public:
	Festival();
	Festival(const char* name, const Projection* projections, size_t projectionsCount);
	Festival(const Festival& other);
	~Festival();
	const char* getName() const;
	void setName(const char* name);
	const Projection* getProjections() const;
	void setProjections(const Projection* projections, size_t projectionsCount);
	size_t getProjectionsCount() const;
};