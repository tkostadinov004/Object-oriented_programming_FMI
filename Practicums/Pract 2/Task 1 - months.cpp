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
};
void printMonth(const Month& month)
{
	switch (month)
	{
		case Month::January:
			cout << "January";
			break;
		case Month::February:
			cout << "February";
			break;
		case Month::March:
			cout << "March";
			break;
		case Month::April:
			cout << "April";
			break;
		case Month::May:
			cout << "May";
			break;
		case Month::June:
			cout << "June";
			break;
		case Month::July:
			cout << "July";
			break;
		case Month::August:
			cout << "August";
			break;
		case Month::September:
			cout << "September";
			break;
		case Month::October:
			cout << "October";
			break;
		case Month::November:
			cout << "November";
			break;
		case Month::December:
			cout << "December";
			break;
	}
}

void printPrevious(const Calendar& date)
{
	printMonth(date.month != Month::January ? (Month)((int)date.month - 1) : Month::December);
	cout << ", " << (date.year ? date.year - 1 : date.year) << endl;
}
void printNext(const Calendar& date)
{
	printMonth(date.month != Month::December ? (Month)((int)date.month + 1) : Month::January);
	cout << ", " << date.year + 1 << endl;
}

int main()
{
	Calendar calendar{ Month::January, 2023 };
	printMonth(calendar.month);
	cout << endl;

	printPrevious(calendar);
	printNext(calendar);
}