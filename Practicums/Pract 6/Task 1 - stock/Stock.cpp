#include <iostream>
#include "Stock.h"
#pragma warning (disable: 4996)

void Stock::copyFrom(const Stock& other)
{
	setAbbreviation(abbreviation);
	setName(name);
	setPrices(prices);
}

Stock::Stock() : Stock("N/A", "undefined", { 0 }) {}

Stock::Stock(const char* abbreviation, const char* name, const float* prices)
{
	setAbbreviation(abbreviation);
	setName(name);
	setPrices(prices);
}

Stock::Stock(const Stock& other)
{
	copyFrom(other);
}

Stock& Stock::operator=(const Stock& other)
{
	if (this == &other)
	{
		return *this;
	}

	copyFrom(other);
	return *this;
}

const char* Stock::getAbbreviation() const
{
	return abbreviation;
}

void Stock::setAbbreviation(const char* abbreviation)
{
	if (!abbreviation)
	{
		return;
	}

	if (strlen(abbreviation) > STOCK_ABBREVIATION_LENGTH)
	{
		return;
	}
	strcpy(this->abbreviation, abbreviation);
}

const char* Stock::getName() const
{
	return name;
}

void Stock::setName(const char* name)
{
	if (!abbreviation)
	{
		return;
	}

	if (strlen(name) > STOCK_NAME_LENGTH)
	{
		return;
	}
	strcpy(this->name, name);
}

const float* Stock::getPrices() const
{
	return prices;
}

void Stock::setPrices(const float* prices)
{
	for (size_t i = 0; i < STOCK_PRICES_COUNT; i++)
	{
		this->prices[i] = prices[i];
	}
}

bool Stock::isProfitable() const
{
	if (((prices[STOCK_PRICES_COUNT - 1] - prices[0]) / prices[0]) * 100 < 10)
	{
		return false;
	}

	int increasingCount = 0;
	for (size_t i = 0; i < STOCK_PRICES_COUNT - 1; i++)
	{
		if (prices[i] < prices[i  + 1])
		{
			increasingCount++;
		}
	}
	return increasingCount > STOCK_PRICES_COUNT / 2;
}
