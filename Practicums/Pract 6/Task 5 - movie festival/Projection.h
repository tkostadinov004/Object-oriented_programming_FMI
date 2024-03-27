#pragma once
#include "Movie.h"

constexpr size_t PROJECTION_DATETIME_LENGTH = 15;
constexpr size_t PROJECTION_HALLNAME_LENGTH = 20;
class Projection
{
	Movie movie;
	char datetime[PROJECTION_DATETIME_LENGTH + 1];
	char hallName[PROJECTION_HALLNAME_LENGTH + 1];
public:
	Projection();
	Projection(const Movie& movie, const char* datetime, const char* hallName);
	Projection(const Projection& other);
	const Movie& getMovie() const;
	void setMovie(const Movie& movie);
	const char* getDatetime() const;
	void setDatetime(const char* datetime);
	const char* getHallName() const;
	void setHallName(const char* hallName);
};