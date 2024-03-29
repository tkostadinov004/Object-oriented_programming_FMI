#include "ShoppingCart.h"

void ShoppingCart::copyFrom(const ShoppingCart& other)
{
	this->capacity = other.capacity;
	this->productsCount = other.productsCount;

	this->products = new Product[other.productsCount];
	for (size_t i = 0; i < other.productsCount; i++)
	{
		this->products[i] = other.products[i];
	}
}
void ShoppingCart::free()
{
	delete[] products;
	products = nullptr;
}

int ShoppingCart::indexOf(const Product& product)
{
	for (size_t i = 0; i < productsCount; i++)
	{
		if (strcmp(product.getName(), products[i].getName()) == 0)
		{
			return i;
		}
	}
	return -1;
}

bool ShoppingCart::containsProduct(const Product& product)
{
	return indexOf(product) > -1;
}

void ShoppingCart::saveToFile(std::ofstream& ofs)
{
	for (size_t i = 0; i < productsCount; i++)
	{
		ofs << products[i].getName() << ";" << products[i].getPrice() << ";" << products[i].getQuantity();
		if (i < productsCount - 1)
		{
			ofs << std::endl;
		}
	}
}

ShoppingCart::ShoppingCart() = default;

ShoppingCart::ShoppingCart(size_t capacity)
{
	this->capacity = capacity;
	this->products = new Product[capacity];
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

void ShoppingCart::addProduct(const Product& product)
{
	if (productsCount + 1 > capacity || containsProduct(product))
	{
		return;
	}

	this->products[this->productsCount++] = product;
}

void ShoppingCart::removeProduct(const Product& product)
{
	if (!containsProduct(product))
	{
		return;
	}

	int index = indexOf(product);
	for (size_t i = index; i < productsCount - 1; i++)
	{
		products[i] = products[i + 1];
	}
	productsCount--;
}

size_t ShoppingCart::getProductsCount() const
{
	return productsCount;
}

bool ShoppingCart::isEmpty() const
{
	return productsCount == 0;
}

float ShoppingCart::getSumOfPrices() const
{
	float sum = 0;
	for (size_t i = 0; i < productsCount; i++)
	{
		sum += products[i].getPrice();
	}
	return sum;
}

void ShoppingCart::sort(bool(*pred)(const Product&, const Product&))
{
	for (size_t i = 0; i < productsCount; i++)
	{
		int minIndex = i;
		for (size_t j = i + 1; j < productsCount; j++)
		{
			if (pred(products[j], products[minIndex]))
			{
				minIndex = j;
			}
		}
		if (i != minIndex)
		{
			std::swap(products[i], products[minIndex]);
		}
	}
}

void ShoppingCart::saveToFile(const char* filename)
{
	if (!filename)
	{
		return;
	}

	std::ofstream ofs(filename);
	if (!ofs.is_open())
	{
		return;
	}

	saveToFile(ofs);
}
