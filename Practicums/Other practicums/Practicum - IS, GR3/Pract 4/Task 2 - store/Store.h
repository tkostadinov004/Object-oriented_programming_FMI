#pragma once
#include "Product.h"

constexpr size_t STORE_NAME_MAXLENGTH = 30;
constexpr size_t STORE_ADDRESS_MAXLENGTH = 30;
constexpr size_t STORE_MAX_PRODUCTS_COUNT = 100;
class Store
{
	char name[STORE_NAME_MAXLENGTH + 1] = "undefined";
	char address[STORE_ADDRESS_MAXLENGTH + 1] = "undefined";
	Product products[STORE_MAX_PRODUCTS_COUNT];
	size_t productsCount = 0;
	float income = 0;
	int indexof(uint8_t productBarcode) const;
public:
	Store();
	Store(const char* name, const char* address, const Product* products, size_t productsCount);

	const char* getName() const;
	const char* getAddress() const;
	const Product* getProducts() const;
	size_t getProductsCount() const;
	float getIncome() const;

	void setName(const char* name);
	void setAddress(const char* address);
	void setProducts(const Product* products, size_t productsCount);

	void loadProduct(const Product& product);
	bool containsProduct(uint8_t productBarcode) const;
	void sellProduct(uint8_t productBarcode, int quantity);
	void print() const;
};