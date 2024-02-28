#include <iostream>
using namespace std;

enum class Month : char
{
	January = 1, February, March, April, May, June, July, August, September, October, November, December
};
struct Calendar
{
	Month month;
	int year;
	int compareTo(const Calendar& other)
	{
		if (year != other.year)
		{
			return year - other.year;
		}

		return (int)month - (int)other.month;
	}
};

enum class Gender : char
{
    Male,
    Female
};
struct Person
{
    char pin[11];
    short postcode;
    Gender gender;
};

enum class Make : char
{
    Ford,
    Tesla,
    Lincoln,
    Cadillac,
    Buick
};
struct Car
{
    Person owner;
    Calendar firstRegistrationDate;
    float price;
    Make make;

    double getValue() const
    {
        return price * firstRegistrationDate.year * 0.1;
    }
    int compareTo(const Car& other)
    {
        return this->getValue() - other.getValue();
    }
    bool isGreaterThan(const Car& other)
    {
        return compareTo(other) > 0;
    }
};

int main()
{
    Car car1{ { "0051234567", 4029, Gender::Male }, {Month::March, 2020}, 12000, Make::Tesla };
    Car car2{ { "0256546787", 2747, Gender::Female }, {Month::July, 2011}, 11500, Make::Ford };

    cout << car1.isGreaterThan(car2);
}