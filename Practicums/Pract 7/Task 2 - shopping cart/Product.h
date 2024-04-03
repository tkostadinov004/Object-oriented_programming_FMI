#pragma once

class Product
{
	char* name = nullptr;
	unsigned quantity = 0;
	float price = 0;
	void copyFrom(const Product& other);
	void free();
public:
	Product();
	Product(const char* name, unsigned quantity, float price);
	Product(const Product& other);
	~Product();
	Product& operator=(const Product& other);

	const char* getName() const;
	unsigned getQuantity() const;
	float getPrice() const;

	void setName(const char* name);
	void setQuantity(int quantity);
	void setPrice(float price);

	float getTotalPrice() const;
	void print() const;
};