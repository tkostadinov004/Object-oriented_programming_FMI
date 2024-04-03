#pragma once
#include "Product.h"

class ShoppingCart
{
	Product* products = nullptr;
	size_t productsCount = 0;
	size_t capacity = 1;

	void copyFrom(const ShoppingCart& other);
	void free();
	void resize(unsigned newCapacity);
	int indexof(const char* name) const;
public:
	ShoppingCart() = default;
	ShoppingCart(const Product* products, size_t productsCount);
	ShoppingCart(const ShoppingCart& other);
	~ShoppingCart();
	ShoppingCart& operator=(const ShoppingCart& other);

	size_t getProductsCount() const;

	void addProduct(const Product& product);
	void removeProduct(const char* name);
	float getTotalPrice() const;
	void print() const;
};