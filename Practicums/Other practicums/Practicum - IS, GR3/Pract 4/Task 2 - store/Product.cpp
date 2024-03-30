#include <iostream>
#include "Product.h"
#pragma warning (disable: 4996)

void Product::copyFrom(const Product& other)
{
    this->barcode = other.barcode;
    this->name = new char[strlen(other.name) + 1];
    strcpy(this->name, other.name);
    this->quantity = other.quantity;
    this->price = other.price;
}

void Product::free()
{
    delete[] name;
    name = nullptr;
    barcode = 0;
    quantity = 0;
    price = 0;
}

Product::Product() = default;

Product::Product(uint8_t barcode, const char* name, int quantity, float price)
{
    setBarcode(barcode);
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

unsigned Product::getBarcode() const
{
    return barcode;
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

void Product::setBarcode(uint8_t barcode)
{
    this->barcode = barcode;
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

void Product::increaseQuantity(int by)
{
    if (by < 0)
    {
        return;
    }
    this->quantity += by;
}

void Product::print() const
{
    std::cout << "Name: " << name << ", Barcode: " << (unsigned)barcode << ", Price: " << price << ", Quantity: " << quantity << std::endl;
}
