#include <iostream>
using namespace std;

namespace Constants
{
	constexpr size_t MAX_LENGTH = 50;
	constexpr size_t MAX_BOOKS_COUNT = 16;
	constexpr size_t MAX_GENRE_NAME_LENGTH = 15;
}
enum class Genre
{
	Novel,
	History,
	Poetry,
	Other
};
struct Book
{
	char title[Constants::MAX_LENGTH + 1];
	char author[Constants::MAX_LENGTH + 1];
	Genre genre;
	int quantity;
};
struct Library
{
	Book books[Constants::MAX_BOOKS_COUNT];
	size_t booksCount = 0;
};
Genre getGenreByName(const char* name)
{
	if (strcmp(name, "Novel") == 0)
	{
		return Genre::Novel;
	}
	else if (strcmp(name, "History") == 0)
	{
		return Genre::History;
	}
	else if (strcmp(name, "Poetry") == 0)
	{
		return Genre::Poetry;
	}
	else
	{
		return Genre::Other;
	}
}
void printGenreName(Genre genre)
{
	switch (genre)
	{
		case Genre::Novel:
			cout << "Novel";
			break;
		case Genre::History:
			cout << "History";
			break;
		case Genre::Poetry:
			cout << "Poetry";
			break;
		case Genre::Other:
			cout << "Other";
			break;
	}
}
Book initializeBook()
{
	Book b{};
	cin.getline(b.title, Constants::MAX_LENGTH);
	cin.getline(b.author, Constants::MAX_LENGTH);

	char genreName[Constants::MAX_GENRE_NAME_LENGTH + 1];
	cin.getline(genreName, Constants::MAX_GENRE_NAME_LENGTH);
	b.genre = getGenreByName(genreName);

	cin >> b.quantity;
	cin.ignore();

	return b;
}
void addToLibrary(const Book& book, Library& library)
{
	if (library.booksCount + 1 > Constants::MAX_BOOKS_COUNT)
	{
		cout << "Capacity reached! Unable to add the book!" << endl;
		return;
	}

	library.books[library.booksCount++] = book;
}
Book* findBookByTitle(const char* title, Library& library)
{
	if (!title)
	{
		return nullptr;
	}

	for (size_t i = 0; i < library.booksCount; i++)
	{
		if (strcmp(title, library.books[i].title) == 0)
		{
			return &library.books[i];
		}
	}
	return nullptr;
}
void takeBookByTitle(const char* title, Library& library)
{
	if (!title)
	{
		return;
	}

	Book* book = findBookByTitle(title, library);
	if (!book)
	{
		return;
	}
	if (book->quantity - 1 < 0)
	{
		return;
	}
	book->quantity--;
}
void returnBookByTitle(const char* title, Library& library)
{
	if (!title)
	{
		return;
	}

	Book* book = findBookByTitle(title, library);
	if (!book)
	{
		return;
	}
	book->quantity++;
}
void printBook(const Book& book)
{
	cout << "Title: " << book.title << ", " << "Author: " << book.author << ", " << "Genre: ";
	printGenreName(book.genre);
	cout << ", " << "Quantity: " << book.quantity << endl;
}
void printLibrary(const Library& library)
{
	cout << "Total books: " << library.booksCount << endl;
	for (size_t i = 0; i < library.booksCount; i++)
	{
		printBook(library.books[i]);
	}
	cout << endl;
}
int main()
{
	Library library{};
	addToLibrary(initializeBook(), library);
	addToLibrary(initializeBook(), library);

	printLibrary(library);

	takeBookByTitle("1984", library);

	printLibrary(library);
}