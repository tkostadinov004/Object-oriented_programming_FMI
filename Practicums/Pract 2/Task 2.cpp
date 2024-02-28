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

struct Product
{
	unsigned id;
	float price;
	Calendar supplyDate;
	Calendar sellDate{ Month::January, 0 };
	bool isProductSold = false;
};
void sell(Product& product, Calendar sellDate)
{
	if (sellDate.compareTo(product.supplyDate) < 0)
	{
		cout << "Error" << endl;
		return;
	}

	product.sellDate = sellDate;
	product.isProductSold = true;
}

int main()
{
	Product p1{ 1, 25.99, {Month::August, 2023} };
	Product p2{ 1, 25.99, {Month::September, 2022} };

	sell(p1, { Month::July, 2023 });
	cout << p1.isProductSold << endl;
	sell(p2, { Month::July, 2023 });
	cout << p2.isProductSold << endl;
	sell(p1, { Month::September, 2023 });
	cout << p1.isProductSold << endl;
}