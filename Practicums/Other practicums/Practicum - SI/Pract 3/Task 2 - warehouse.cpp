#include <iostream>
#include <fstream>

constexpr size_t MAX_NAME_LENGTH = 100;

enum class Category
{
	UNDEFINED, ELECTRONICS, CLOTHING, BOOKS, FOOD, BEAUTY
};
Category readCategory() {

	char category[MAX_NAME_LENGTH];
	std::cin.getline(category, MAX_NAME_LENGTH);

	if (strcmp(category, "ELECTRONICS") == 0)
	{
		return Category::ELECTRONICS;
	}
	else if (strcmp(category, "CLOTHING") == 0)
	{
		return Category::CLOTHING;
	}
	else if (strcmp(category, "BOOKS") == 0)
	{
		return Category::BOOKS;
	}
	else if (strcmp(category, "FOOD") == 0)
	{
		return Category::FOOD;
	}
	else if (strcmp(category, "BEAUTY") == 0)
	{
		return Category::BEAUTY;
	}
	else
	{
		return Category::UNDEFINED;
	}
}
void printCategory(const Category& category) {

	switch (category)
	{
		case Category::BEAUTY:
			std::cout << "BEAUTY"; 
			break;
		case Category::BOOKS:
			std::cout << "BOOKS"; 
			break;
		case Category::ELECTRONICS:
			std::cout << "ELECTRONICS"; 
			break;
		case Category::FOOD:
			std::cout << "FOOD"; 
			break;
		case Category::CLOTHING:
			std::cout << "CLOTHING"; 
			break;
		case Category::UNDEFINED:
			std::cout << "UNDEFINED"; 
			break;
	}
}
struct Product
{
	char name[MAX_NAME_LENGTH + 1];
	char supplier[MAX_NAME_LENGTH + 1];
	int quantity = 0;
	float price = 0;
	Category category;
};
struct Warehouse
{
	Product* products = nullptr;
	size_t productsCount = 0;
};
size_t getFileSize(std::ifstream& ifs)
{
	int currentPos = ifs.tellg();
	ifs.seekg(0, std::ios::end);

	size_t size = ifs.tellg();
	ifs.seekg(currentPos);
	ifs.clear();

	return size;
}
void loadFromFile(std::ifstream& ifs, Warehouse& warehouse)
{
	warehouse.productsCount = getFileSize(ifs) / sizeof(Product);
	warehouse.products = new Product[warehouse.productsCount];
	ifs.read((char*)warehouse.products, warehouse.productsCount * sizeof(Product));
}
void loadFromFile(const char* filename, Warehouse& warehouse)
{
	if (!filename)
	{
		return;
	}

	std::ifstream ifs(filename, std::ios::binary);
	if (!ifs.is_open())
	{
		return;
	}

	loadFromFile(ifs, warehouse);
}
void readProduct(Product& product)
{
	std::cin.getline(product.name, MAX_NAME_LENGTH);
	std::cin.getline(product.supplier, MAX_NAME_LENGTH);
	std::cin >> product.quantity >> product.price;
	product.category = readCategory();
}
void addProducts(std::ofstream& ofs, size_t amount)
{
	for (size_t i = 0; i < amount; i++)
	{
		Product product{};
		readProduct(product);
		if (product.quantity < 0 || product.price <= 0 || product.category == Category::UNDEFINED)
		{
			continue;
		}
		ofs.write((const char*)&product, sizeof(Product));
	}
}
void addProducts(const char* filename, size_t amount)
{
	if (!filename)
	{
		return;
	}

	std::ofstream ofs(filename, std::ios::app || std::ios::binary);
	if (!ofs.is_open())
	{
		return;
	}

	addProducts(ofs, amount);
}
void changeQuantity(Product& product, int newQuantity)
{
	product.quantity = newQuantity;
}
void writeToFile(std::ofstream& ofs, const Warehouse& warehouse)
{
	ofs.write((const char*)warehouse.products, sizeof(Product) * warehouse.productsCount);
}
void writeToFile(const char* filename, const Warehouse& warehouse)
{
	if (!filename)
	{
		return;
	}

	std::ofstream ofs(filename, std::ios::binary);
	if (!ofs.is_open())
	{
		return;
	}

	writeToFile(ofs, warehouse);
}
void printProduct(const Product& product)
{
	std::cout << product.name << " " << product.supplier << " " << product.quantity << " " << product.price << " ";
	printCategory(product.category);
	std::cout << std::endl;
}
void printProducts(const Warehouse& warehouse)
{
	for (size_t i = 0; i < warehouse.productsCount; i++)
	{
		printProduct(warehouse.products[i]);
	}
}
int indexof(const char* name, const Warehouse& warehouse)
{
	if (!name)
	{
		return -1;
	}

	for (size_t i = 0; i < warehouse.productsCount; i++)
	{
		if (strcmp(name, warehouse.products[i].name) == 0)
		{
			return i;
		}
	}
	return -1;
}
void printByName(const char* name, const Warehouse& warehouse)
{
	if (!name)
	{
		return;
	}

	int index = indexof(name, warehouse);
	if (index == -1)
	{
		return;
	}

	printProduct(warehouse.products[index]);
}
void saveByCategory(std::ofstream& ofs, const Warehouse& warehouse, Category category)
{
	for (size_t i = 0; i < warehouse.productsCount; i++)
	{
		if (warehouse.products[i].category == category)
		{
			ofs.write((const char*)&warehouse.products[i], sizeof(warehouse.products[i]));
		}
	}
}
void saveByCategory(const char* filename, const Warehouse& warehouse, Category category)
{
	if (!filename)
	{
		return;
	}
	
	std::ofstream ofs(filename, std::ios::binary);
	if (!ofs.is_open())
	{
		return;
	}

	saveByCategory(ofs, warehouse, category);
}
int main()
{
	/*Product products[2] = { {"Taco", "Taco Bell", 26, 8.30, Category::FOOD }, {"1984", "Ciela", 5, 12.20, Category::BOOKS } };
	Warehouse warehouse{ products, 2 };
	writeToFile("warehouse.dat", warehouse);*/

	Warehouse warehouse{};
	loadFromFile("warehouse.dat", warehouse);

	printProducts(warehouse);

	changeQuantity(warehouse.products[0], warehouse.products[0].quantity - 1);
	writeToFile("warehouse.dat", warehouse);

	Product products[2] = { {"TestFood", "TestProvider", 21, 6.30, Category::FOOD }, {"TestClothing", "TestClothingProvider", 15, 12.40, Category::CLOTHING } };
	Warehouse warehouse2{ products, 2 };
	saveByCategory("warehouse2.dat", warehouse2, Category::CLOTHING);

	delete[] warehouse.products;
}