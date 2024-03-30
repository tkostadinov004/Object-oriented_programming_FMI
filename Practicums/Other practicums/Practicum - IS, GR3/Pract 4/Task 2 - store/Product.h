#pragma once
#include <iostream>

class Product
{
	uint8_t barcode = 0;
	char* name = nullptr;
	unsigned quantity = 0;
	float price = 0;
	void copyFrom(const Product& other);
	void free();
public:
	Product();
	Product(uint8_t barcode, const char* name, int quantity, float price);
	Product(const Product& other);
	~Product();
	Product& operator=(const Product& other);

	unsigned getBarcode() const;
	const char* getName() const;
	unsigned getQuantity() const;
	float getPrice() const;

	void setBarcode(uint8_t barcode);
	void setName(const char* name);
	void setQuantity(int quantity);
	void setPrice(float price);

	void increaseQuantity(int by);
	void print() const;
};