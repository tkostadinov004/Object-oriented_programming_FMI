#include <iostream>
using namespace std;

struct Product
{
	char description[32];
	int partNum;
	double cost;
	void print() const
	{
		cout << "Description: " << description << ", " << "Number: " << partNum << ", " << "Cost: $" << cost << endl;
	}
};

void initializeProducts(Product* products, size_t size)
{
	if (!products)
	{
		return;
	}
	for (size_t i = 0; i < size; i++)
	{
		products[i] = { 0, 0, 0 };
	}
}
void printProducts(const Product* products, size_t size)
{
	if (!products)
	{
		return;
	}
	for (size_t i = 0; i < size; i++)
	{
		products[i].print();
	}
}
int main()
{
	Product screwDriver{ "screw driver", 456, 5.50 };
	Product hammer{ "hammer", 324, 8.20 };

	screwDriver.print();
	hammer.print();
	cout << endl;
	
	constexpr size_t PRODUCTS_SIZE = 5;
	Product products[PRODUCTS_SIZE];
	initializeProducts(products, PRODUCTS_SIZE);

	products[0] = { "screw driver", 456, 5.50 };
	products[1] = { "hammer", 324, 8.20 };
	products[2] = { "socket", 777, 6.80 };
	products[3] = { "plier", 123, 10.80 };
	products[4] = { "hand-saw", 555, 12.80 };

	printProducts(products, PRODUCTS_SIZE);
}

