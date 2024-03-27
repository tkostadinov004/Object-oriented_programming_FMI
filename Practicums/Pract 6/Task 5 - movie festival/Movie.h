#pragma once

constexpr size_t MOVIE_TITLE_LENGTH = 30;
constexpr size_t MOVIE_DIRECTOR_LENGTH = 30;
class Movie
{
	char title[MOVIE_TITLE_LENGTH + 1];
	char director[MOVIE_DIRECTOR_LENGTH + 1];
	int length;
public:
	Movie();
	Movie(const char* title, const char* director, int length);
	const char* getTitle() const;
	void setTitle(const char* title);
	const char* getDirector() const;
	void setDirector(const char* director);
	int getLength() const;
	void setLength(int length);
};