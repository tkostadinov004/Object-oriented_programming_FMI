#include <iostream>
#include "Product.h"
#include "ShoppingCart.h"

int main()
{
    Product products[3] = { Product("Pineapples", 1000, 5), Product("IPhone", 10, 1000.20), Product("Laptop", 20, 700)};
    ShoppingCart cart(products, 3);

    std::cout << cart.getProductsCount() << std::endl;
    cart.print();
    std::cout << std::endl << std::endl;
    cart.addProduct(Product("TestProduct", 100, 105));
    cart.print();
    std::cout << std::endl << std::endl;

    cart.removeProduct("askjd"); //shouldn't remove
    cart.removeProduct("Pineapples");

    cart.print();
}