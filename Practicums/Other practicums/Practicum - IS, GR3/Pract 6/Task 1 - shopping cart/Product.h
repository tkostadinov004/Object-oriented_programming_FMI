#pragma once

class Product
{
	char* name = nullptr;
	float price = 0;
	unsigned quantity = 0;
	void copyFrom(const Product& other);
	void free();
public:
	Product();
	Product(const char* name, float price, unsigned quantity);
	Product(const Product& other);
	~Product();
	Product& operator=(const Product& other);

	const char* getName() const;
	float getPrice() const;
	unsigned getQuantity() const;

	void setName(const char* name);
	void setPrice(float price);
	void setQuantity(unsigned quantity);
};