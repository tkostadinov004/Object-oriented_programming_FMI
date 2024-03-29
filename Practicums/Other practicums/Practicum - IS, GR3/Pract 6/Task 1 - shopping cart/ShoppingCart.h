#pragma once
#include <fstream>
#include "Product.h"

class ShoppingCart
{
	Product* products = nullptr;
	size_t productsCount = 0;
	size_t capacity = 0;
	void copyFrom(const ShoppingCart& other);
	void free();
	int indexOf(const Product& product);
	bool containsProduct(const Product& product);
	void saveToFile(std::ofstream& ofs);
public:
	ShoppingCart();
	ShoppingCart(size_t capacity);
	ShoppingCart(const ShoppingCart& other);
	~ShoppingCart();
	ShoppingCart& operator=(const ShoppingCart& other);

	void addProduct(const Product& product);
	void removeProduct(const Product& product);
	size_t getProductsCount() const;
	bool isEmpty() const;
	float getSumOfPrices() const;
	void sort(bool(*pred)(const Product&, const Product&));
	void saveToFile(const char* filename);
};