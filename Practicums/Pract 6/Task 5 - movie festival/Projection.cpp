#include <iostream>
#include "Projection.h"
#pragma warning (disable: 4996)

Projection::Projection() : datetime("undefined"), hallName("undefined") {}

Projection::Projection(const Movie& movie, const char* datetime, const char* hallName)
{
    setMovie(movie);
    setDatetime(datetime);
    setHallName(hallName);
}

const Movie& Projection::getMovie() const
{
    return movie;
}

void Projection::setMovie(const Movie& movie)
{
    this->movie = movie;
}

const char* Projection::getDatetime() const
{
    return datetime;
}

void Projection::setDatetime(const char* datetime)
{
    if (!datetime)
    {
        return;
    }

    if (strlen(datetime) > PROJECTION_DATETIME_LENGTH)
    {
        return;
    }
    strcpy(this->datetime, datetime);
}

const char* Projection::getHallName() const
{
    return hallName;
}

void Projection::setHallName(const char* hallName)
{
    if (!hallName)
    {
        return;
    }

    if (strlen(hallName) > PROJECTION_HALLNAME_LENGTH)
    {
        return;
    }
    strcpy(this->hallName, hallName);
}
