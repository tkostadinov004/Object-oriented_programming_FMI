#include <iostream>
#include <fstream>

struct Customer
{
    char* name;
    char* id;
    unsigned age;
};
void serializeCustomer(std::ofstream& ofs, const Customer& customer)
{
    size_t nameLength = strlen(customer.name);
    size_t idLength = strlen(customer.id);

    ofs.write((const char*)&nameLength, sizeof(nameLength));
    ofs.write(customer.name, nameLength + 1);
    ofs.write((const char*)&idLength, sizeof(idLength));
    ofs.write(customer.id, idLength + 1);

    ofs.write((const char*)&customer.age, sizeof(customer.age));
}
void deserializeCustomer(std::ifstream& ifs, Customer& customer)
{
    size_t nameLength = 0;
    ifs.read((char*)&nameLength, sizeof(nameLength));
    customer.name = new char[nameLength + 1];
    ifs.read(customer.name, nameLength + 1);

    size_t idLength = 0;
    ifs.read((char*)&idLength, sizeof(idLength));
    customer.id = new char[idLength + 1];
    ifs.read(customer.id, idLength + 1);

    ifs.read((char*)&customer.age, sizeof(customer.age));
}

struct Order
{
    float price;
    float vat;
    Customer customer;
};
void writeOrderToFile(std::ofstream& ofs, const Order& order)
{
    serializeCustomer(ofs, order.customer);
    ofs.write((const char*)&order.price, sizeof(order.price));
    ofs.write((const char*)&order.vat, sizeof(order.vat));
}
void writeOrdersToFile(std::ofstream& ofs, const Order* orders, size_t size)
{
    if (!orders)
    {
        return;
    }

    ofs.write((const char*)&size, sizeof(size));
    for (size_t i = 0; i < size; i++)
    {
        writeOrderToFile(ofs, orders[i]);
    }
}
void writeOrdersToFile(const char* filename, const Order* orders, size_t size)
{
    if (!filename || !orders)
    {
        return;
    }

    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs.is_open())
    {
        return;
    }

    writeOrdersToFile(ofs, orders, size);
}
void readOrderFromFile(std::ifstream& ifs, Order& order)
{
    deserializeCustomer(ifs, order.customer);
    ifs.read((char*)&order.price, sizeof(order.price));
    ifs.read((char*)&order.vat, sizeof(order.vat));
}
void readOrdersFromFile(std::ifstream& ifs, Order*& orders, size_t& size)
{
    ifs.read((char*)&size, sizeof(size));

    orders = new Order[size];
    for (size_t i = 0; i < size; i++)
    {
        readOrderFromFile(ifs, orders[i]);
    }
}
void readOrdersFromFile(const char* filename, Order*& orders, size_t& size)
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

    readOrdersFromFile(ifs, orders, size);
}
void freeMemory(Order* orders, size_t size)
{
    if (!orders)
    {
        return;
    }

    for (size_t i = 0; i < size; i++)
    {
        delete[] orders[i].customer.name;
        delete[] orders[i].customer.id;
    }
    delete orders;
}
void printOrder(const Order& order)
{
    std::cout << "Price: " << order.price << std::endl << "VAT: " << order.vat << std::endl;
    std::cout << "Name: " << order.customer.name << ", Id: " << order.customer.id << ", Age: " << order.customer.age << std::endl;
}
int main()
{
    /*Order order1 = { 10.5, 0.2, {new char[5] {"Ivan"}, new char[6] {"12345"}, 20} };
    Order order2 = { 22, 0.15, {new char[6] {"Petur"}, new char[7] {"552372"}, 25} };
    Order orders[] = { order1, order2 };

    writeOrdersToFile("orders.dat", orders, 2);*/

    Order* orders = nullptr;
    size_t size = 0;
    readOrdersFromFile("orders.dat", orders, size);

    for (size_t i = 0; i < size; i++)
    {
        printOrder(orders[i]);
        std::cout << "---------------------" << std::endl;
    }

    freeMemory(orders, size);
}