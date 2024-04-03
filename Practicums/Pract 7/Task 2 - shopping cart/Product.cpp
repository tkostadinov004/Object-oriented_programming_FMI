#include <iostream>
#include "Product.h"
#pragma warning (disable: 4996)

void Product::copyFrom(const Product& other)
{
    this->name = new char[strlen(other.name) + 1];
    strcpy(this->name, other.name);
    this->quantity = other.quantity;
    this->price = other.price;
}

void Product::free()
{
    delete[] name;
    name = nullptr;
    quantity = 0;
    price = 0;
}

Product::Product() : Product("undefined", 0, 0) {}

Product::Product(const char* name, unsigned quantity, float price)
{
    setName(name);
    setQuantity(quantity);
    setPrice(price);
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

unsigned Product::getQuantity() const
{
    return quantity;
}

float Product::getPrice() const
{
    return price;
}

void Product::setName(const char* name)
{
    if (!name || this->name == name)
    {
        return;
    }

    delete[] this->name;
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

void Product::setQuantity(int quantity)
{
    if (quantity < 0)
    {
        return;
    }
    this->quantity = quantity;
}

void Product::setPrice(float price)
{
    if (price < 0)
    {
        return;
    }
    this->price = price;
}

float Product::getTotalPrice() const
{
    return quantity * price;
}

void Product::print() const
{
    std::cout << "Product: " << name << ", Price: " << price << ", Quantity: " << quantity << std::endl;
}
