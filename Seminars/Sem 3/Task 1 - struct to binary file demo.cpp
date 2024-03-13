#include <iostream>
#include <fstream>

constexpr size_t CITY_NAME_LENGTH = 20;
struct City
{
    char name[CITY_NAME_LENGTH + 1];
    unsigned population = 0;
    float area = 0;
};
void serializeCities(std::ofstream& ofs, const City* cities, size_t size)
{
    ofs.write((const char*)cities, size * sizeof(City));
}
void serializeCities(const char* filename, const City* cities, size_t size)
{
    if (!filename || !cities)
    {
        return;
    }

    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs.is_open())
    {
        return;
    }

    serializeCities(ofs, cities, size);
}
unsigned getFileSize(std::ifstream& ifs)
{
    int currentPos = ifs.tellg();
    ifs.seekg(0, std::ios::end);
    unsigned size = ifs.tellg();

    ifs.clear();
    ifs.seekg(currentPos);

    return size;
}
City* deserializeCities(std::ifstream& ifs, size_t& size)
{
    size = getFileSize(ifs) / sizeof(City);

    City* cities = new City[size];
    ifs.read((char*)cities, size * sizeof(City));

    return cities;
}
City* deserializeCities(const char* filename, size_t& size)
{
    if (!filename)
    {
        return nullptr;
    }

    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs.is_open())
    {
        return nullptr;
    }

    return deserializeCities(ifs, size);
}
int main()
{
    /*City cities[] = { {"Fargo", 126748, 131.5}, {"Boise", 237446, 220.1}, {"Savannah", 147088, 293.4} };
    serializeCities("cities.dat", cities, 3);*/

    size_t size = 0;
    City* cities = deserializeCities("cities.dat", size);

    for (size_t i = 0; i < size; i++)
    {
        std::cout << cities[i].name << " " << cities[i].population << " " << cities[i].area << std::endl;
    }
    delete[] cities;
}