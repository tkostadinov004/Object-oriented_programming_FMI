#include <iostream>
#include "Product.h"
#pragma warning (disable: 4996)

void Product::copyFrom(const Product& other)
{
	this->name = new char[strlen(other.name) + 1];
	strcpy(this->name, other.name);

	this->price = other.price;
	this->quantity = other.quantity;
}
void Product::free()
{
	delete[] name;
	name = nullptr;
}
Product::Product() = default;
Product::Product(const char* name, float price, unsigned quantity)
{
	setName(name);
	setPrice(price);
	setQuantity(quantity);
}
Product::Product(const Product& other)
{
	copyFrom(other);
}
Product::~Product()
{
	free();
}
Product& Product::operator=(const Product& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
const char* Product::getName() const
{
	return name;
}

float Product::getPrice() const
{
	return price;
}

unsigned Product::getQuantity() const
{
	return quantity;
}

void Product::setName(const char* name)
{
	if (!name)
	{
		return;
	}

	if (this->name == name)
	{
		return;
	}

	delete[] this->name;
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void Product::setPrice(float price)
{
	if (price < 0)
	{
		return;
	}
	this->price = price;
}

void Product::setQuantity(unsigned quantity)
{
	this->quantity = quantity;
}

