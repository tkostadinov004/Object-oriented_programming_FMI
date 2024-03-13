#include <iostream>
#include <fstream>

size_t getFileSize(std::ifstream& ifs)
{
    int currentPos = ifs.tellg();
    ifs.seekg(0, std::ios::end);
    size_t size = ifs.tellg();

    ifs.clear();
    ifs.seekg(currentPos);

    return size;
}
int main()
{
    std::ifstream ifs("cities.dat", std::ios::binary);
    if (!ifs.is_open())
    {
        return -1;
    }

    std::cout << getFileSize(ifs);
}