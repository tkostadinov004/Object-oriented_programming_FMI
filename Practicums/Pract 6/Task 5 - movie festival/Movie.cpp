#include <iostream>
#include "Movie.h"
#pragma warning (disable: 4996)

Movie::Movie() : title("undefined"), director("undefined"), length(0) {}

Movie::Movie(const char* title, const char* director, int length)
{
    setTitle(title);
    setDirector(director);
    setLength(length);
}

const char* Movie::getTitle() const
{
    return title;
}

void Movie::setTitle(const char* title)
{
    if (!title)
    {
        return;
    }

    if (strlen(title) > MOVIE_TITLE_LENGTH)
    {
        return;
    }
    strcpy(this->title, title);
}

const char* Movie::getDirector() const
{
    return director;
}

void Movie::setDirector(const char* director)
{
    if (!director)
    {
        return;
    }

    if (strlen(director) > MOVIE_DIRECTOR_LENGTH)
    {
        return;
    }
    strcpy(this->director, director);
}

int Movie::getLength() const
{
    return length;
}

void Movie::setLength(int length)
{
    if (length <= 0)
    {
        return;
    }

    this->length = length;
}
