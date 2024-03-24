#include <iostream>
#include <fstream>
#pragma warning (disable: 4996)

constexpr size_t MAX_MOVIES_COUNT = 10;

enum class Genre
{
    Action = 1,
    Comedy = 2,
    Drama = 4,
    Fantasy = 8,
    Horror = 16,
    Mystery = 32,
    Romance = 64,
};
const char* getGenreName(Genre genre)
{
    switch (genre)
    {
    case Genre::Action:
        return "Action";
        break;
    case Genre::Comedy:
        return "Comedy";
        break;
    case Genre::Drama:
        return "Drama";
        break;
    case Genre::Fantasy:
        return "Fantasy";
        break;
    case Genre::Horror:
        return "Horror";
        break;
    case Genre::Mystery:
        return "Mystery";
        break;
    case Genre::Romance:
        return "Romance";
        break;
    default:
        return "Undefined";
        break;
    }
}
class Movie
{
    char* name = nullptr;
    char* director = nullptr;
    unsigned duration;
    unsigned char genreValue;
public:
    Movie() : Movie("undefined", "undefined", 0, 0) {}
    Movie(const char* name, const char* director, unsigned duration, unsigned char genreValue)
    {
        setName(name);
        setDirector(director);
        setDuration(duration);
        this->genreValue = genreValue;
    }
    Movie(const Movie& other)
    {
        this->copyFrom(other);
    }
    ~Movie()
    {
        delete[] name;
        delete[] director;
    }
    const char* getName() const
    {
        return name;
    }
    void setName(const char* name)
    {
        if (!name)
        {
            return;
        }

        delete[] this->name;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }
    const char* getDirector() const
    {
        return director;
    }
    void setDirector(const char* director)
    {
        if (!director)
        {
            return;
        }

        delete[] this->director;
        this->director = new char[strlen(director) + 1];
        strcpy(this->director, director);
    }
    unsigned getDuration() const
    {
        return duration;
    }
    void setDuration(unsigned duration)
    {
        this->duration = duration;
    }
    void addGenre(Genre genre)
    {
        this->genreValue |= (unsigned char)genre;
    }
    void removeGenre(Genre genre)
    {
        this->genreValue &= (~((unsigned char)genre));
    }
    void print() const
    {
        std::cout << "Name: " << name << ", Director: " << director << ", Genres: ";
        for (size_t i = 0; i < 7; i++)
        {
            if (((1 << i) & genreValue) != 0)
            {
                std::cout << getGenreName((Genre)(1 << i)) << " / ";
            }
        }
        std::cout << std::endl;
    }
    void copyFrom(const Movie& other)
    {
        this->duration = other.duration;
        this->genreValue = other.genreValue;

        setName(other.name);
        setDirector(other.director);
    }
};
class MovieSchedule
{
    Movie movies[MAX_MOVIES_COUNT];
    size_t moviesCount;
public:
    MovieSchedule() : movies(), moviesCount(0) {}
    void addMovie(const Movie& movie)
    {
        if (moviesCount + 1 > MAX_MOVIES_COUNT)
        {
            return;
        }

        movies[moviesCount++].copyFrom(movie);
    }
    void print() const
    {
        unsigned minutes = 0;
        for (size_t i = 0; i < moviesCount; i++)
        {
            std::cout << movies[i].getName() << " - " << (minutes / 60) << ":" << (minutes % 60) << std::endl;
            minutes += movies[i].getDuration();
        }
    }
    unsigned getTotalDuration() const
    {
        unsigned sum = 0;
        for (size_t i = 0; i < moviesCount; i++)
        {
            sum += movies[i].getDuration();
        }
        return sum;
    }
};
int main()
{
    Movie m1("Django Unchained", "Quentin Tarantino", 165, (unsigned char)Genre::Drama | (unsigned char)Genre::Action);
    Movie m2("O Brother, Where Art Thou", "The Cohen Brothers", 107, (unsigned char)Genre::Comedy | (unsigned char)Genre::Action | (unsigned char)Genre::Romance);
    Movie m3("Superbad", "Greg Mottola", 113, (unsigned char)Genre::Comedy);
    m1.print();
    m2.print();
    m3.print();

    MovieSchedule schedule;
    schedule.addMovie(m1);
    schedule.addMovie(m2);
    schedule.addMovie(m3);
    std::cout << schedule.getTotalDuration() << std::endl;
    schedule.print();
}