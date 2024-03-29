#include <iostream>
#include "ShoppingCart.h"

int main()
{
	Product products[3] = { Product("IPhone", 1000, 10), Product("TV", 600, 5), Product("Pineapple", 5, 50)};
	ShoppingCart cart(3);
	std::cout << cart.isEmpty() << std::endl;
	for (size_t i = 0; i < 3; i++)
	{
		cart.addProduct(products[i]);
	}
	cart.addProduct(Product("Test", 234, 22)); //shouldn't add
	
	std::cout << cart.getProductsCount() << std::endl;
	std::cout << cart.getSumOfPrices() << std::endl;
	std::cout << cart.isEmpty() << std::endl;
	
	cart.removeProduct(Product("IPhone", 1000, 10));
	std::cout << cart.getProductsCount() << std::endl;
	std::cout << cart.getSumOfPrices() << std::endl;

	cart.removeProduct(Product("bfgfdg", 1000, 10)); // shoudln't remove
	std::cout << cart.getProductsCount() << std::endl;
	std::cout << cart.getSumOfPrices() << std::endl;

	cart.saveToFile("result.txt");
}