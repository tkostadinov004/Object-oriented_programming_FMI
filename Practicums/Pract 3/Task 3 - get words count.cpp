#include <iostream>
#include <fstream>

constexpr size_t BUFFER_SIZE = 1024;

unsigned getWordsCount(const char* fileName)
{
    if (!fileName)
    {
        return 0;
    }

    std::ifstream file(fileName);
    if (!file.is_open())
    {
        return 0;
    }

    unsigned count = 0;
    char buffer[BUFFER_SIZE];
    while (file >> buffer)
    {
        count++;
    }
    return count;
}

int main()
{
    std::cout << getWordsCount("lorem.txt");;
}