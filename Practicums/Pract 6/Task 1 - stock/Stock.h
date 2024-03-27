#pragma once

constexpr size_t STOCK_ABBREVIATION_LENGTH = 5;
constexpr size_t STOCK_NAME_LENGTH = 20;
constexpr size_t STOCK_PRICES_COUNT = 12;
class Stock
{
	char abbreviation[STOCK_ABBREVIATION_LENGTH + 1] = "N/A";
	char name[STOCK_NAME_LENGTH + 1] = "undefined";
	float prices[STOCK_PRICES_COUNT] = { 0 };
	void copyFrom(const Stock& other);
public:
	Stock();
	Stock(const char* abbreviation, const char* name, const float* prices);
	Stock& operator=(const Stock& other);
	const char* getAbbreviation() const;
	void setAbbreviation(const char* abbreviation);
	const char* getName() const;
	void setName(const char* name);
	const float* getPrices() const;
	void setPrices(const float* prices);
	bool isProfitable() const;
};