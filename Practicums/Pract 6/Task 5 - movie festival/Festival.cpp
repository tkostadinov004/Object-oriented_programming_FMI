#include <iostream>
#include "Festival.h"
#pragma warning (disable: 4996)

void Festival::copyFrom(const Festival& other)
{
    setName(other.name);
    setProjections(other.projections, other.projectionsCount);
}

Festival::Festival() : Festival(name, nullptr, 0)
{
}

Festival::Festival(const char* name, const Projection* projections, size_t projectionsCount)
{
    setName(name);
    setProjections(projections, projectionsCount);
}

Festival::Festival(const Festival& other)
{
    copyFrom(other);
}

Festival::~Festival()
{
    delete[] projections;
}

const char* Festival::getName() const
{
    return name;
}

void Festival::setName(const char* name)
{
    if (!name)
    {
        return;
    }

    if (strlen(name) > FESTIVAL_NAME_LENGTH)
    {
        return;
    }

    strcpy(this->name, name);
}

const Projection* Festival::getProjections() const
{
    return projections;
}

void Festival::setProjections(const Projection* projections, size_t projectionsCount)
{
    if (!projections)
    {
        return;
    }

    delete[] this->projections;
    this->projectionsCount = projectionsCount;
    this->projections = new Projection[projectionsCount];
    for (size_t i = 0; i < projectionsCount; i++)
    {
        this->projections[i] = projections[i];
    }
}

size_t Festival::getProjectionsCount() const
{
    return projectionsCount;
}
