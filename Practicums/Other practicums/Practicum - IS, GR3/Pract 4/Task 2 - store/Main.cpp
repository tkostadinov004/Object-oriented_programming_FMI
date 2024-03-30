#include <iostream>
#include "Product.h"
#include "Store.h"

int main()
{
	Product products[3] = { Product(234, "Phone", 10, 1000), Product(102, "Pineapple", 100, 5), Product(92, "Laptop", 20, 600)};
	Store store("Store", "Example Address", products, 3);

	std::cout << store.containsProduct(234) << std::endl;
	std::cout << store.containsProduct(0) << std::endl;

	store.print();
}