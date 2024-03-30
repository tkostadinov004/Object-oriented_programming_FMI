#include "Store.h"
#pragma warning (disable: 4996)

int Store::indexof(uint8_t productBarcode) const
{
	for (size_t i = 0; i < productsCount; i++)
	{
		if (productBarcode == products[i].getBarcode())
		{
			return i;
		}
	}
    return -1;
}

Store::Store() = default;

Store::Store(const char* name, const char* address, const Product* products, size_t productsCount)
{
	setName(name);
	setAddress(address);
	setProducts(products, productsCount);
}

const char* Store::getName() const
{
	return name;
}

const char* Store::getAddress() const
{
	return address;
}

const Product* Store::getProducts() const
{
	return products;
}

size_t Store::getProductsCount() const
{
	return productsCount;
}

float Store::getIncome() const
{
	return income;
}

void Store::setName(const char* name)
{
	if (!name || strlen(name) > STORE_NAME_MAXLENGTH)
	{
		return;
	}
	strcpy(this->name, name);
}

void Store::setAddress(const char* address)
{
	if (!address || strlen(address) > STORE_ADDRESS_MAXLENGTH)
	{
		return;
	}
	strcpy(this->address, address);
}

void Store::setProducts(const Product* products, size_t productsCount)
{
	if (!products)
	{
		return;
	}
	for (size_t i = 0; i < productsCount; i++)
	{
		loadProduct(products[i]);
	}
}

void Store::loadProduct(const Product& product)
{
	if (containsProduct(product.getBarcode()))
	{
		return;
	}

	if (productsCount + 1 > STORE_MAX_PRODUCTS_COUNT)
	{
		return;
	}

	products[productsCount++] = product;
}

bool Store::containsProduct(uint8_t productBarcode) const
{
    return indexof(productBarcode) > -1;
}

void Store::sellProduct(uint8_t productBarcode, int quantity)
{
	if (!containsProduct(productBarcode))
	{
		return;
	}
	Product& product = products[indexof(productBarcode)];
	if (product.getQuantity() < quantity)
	{
		income += product.getQuantity() * product.getPrice();
		product.setQuantity(0);
	}
	else
	{
		income += quantity * product.getPrice();
		product.setQuantity(product.getQuantity() - quantity);
	}
}

void Store::print() const
{
	std::cout << "Store: " << name << " at " << address << " with " << productsCount << " products." << std::endl;
	for (size_t i = 0; i < productsCount; i++)
	{
		products[i].print();
	}
}
