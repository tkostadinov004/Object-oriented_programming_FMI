#include <iostream>
#include "ShoppingCart.h"
#include "HelperFunctions.h"

void ShoppingCart::copyFrom(const ShoppingCart& other)
{
    this->products = new Product[other.capacity];
    for (size_t i = 0; i < other.productsCount; i++)
    {
        this->products[i] = other.products[i];
    }
    this->productsCount = other.productsCount;
    this->capacity = other.capacity;
}

void ShoppingCart::free()
{
    delete[] products;
    products = nullptr;
    productsCount = 0;
}

void ShoppingCart::resize(unsigned newCapacity)
{
    Product* temp = new Product[newCapacity];
    for (size_t i = 0; i < productsCount; i++)
    {
        temp[i] = this->products[i];
    }
    capacity = newCapacity;
    delete[] products;
    products = temp;
}

int ShoppingCart::indexof(const char* name) const
{
    if (!name)
    {
        return -1;
    }

    for (size_t i = 0; i < productsCount; i++)
    {
        if (strcmp(name, products[i].getName()) == 0)
        {
            return i;
        }
    }
    return -1;
}

ShoppingCart::ShoppingCart(const Product* products, size_t productsCount)
{
    if (!products)
    {
        return;
    }

    this->capacity = getNextPowerOfTwo(productsCount);
    this->products = new Product[this->capacity];
    for (size_t i = 0; i < productsCount; i++)
    {
        addProduct(products[i]);
    }
}

ShoppingCart::ShoppingCart(const ShoppingCart& other)
{
    copyFrom(other);
}

ShoppingCart::~ShoppingCart()
{
    free();
}

ShoppingCart& ShoppingCart::operator=(const ShoppingCart& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

size_t ShoppingCart::getProductsCount() const
{
    return productsCount;
}

void ShoppingCart::addProduct(const Product& product)
{
    if (productsCount + 1 > capacity)
    {
        resize(capacity * 2);
    }
    products[productsCount++] = product;
}

void ShoppingCart::removeProduct(const char* name)
{
    if (!name)
    {
        return;
    }

    int index = indexof(name);
    if (index == -1)
    {
        return;
    }

    for (size_t i = index; i < productsCount - 1; i++)
    {
        products[i] = products[i + 1];
    }
    productsCount--;
}

float ShoppingCart::getTotalPrice() const
{
    float sum = 0;
    for (size_t i = 0; i < productsCount; i++)
    {
        sum += products[i].getTotalPrice();
    }
    return sum;
}

void ShoppingCart::print() const
{
    std::cout << "Shopping cart with " << productsCount << " products. " << std::endl;
    for (size_t i = 0; i < productsCount; i++)
    {
        products[i].print();
    }
}
