#include <iostream>
#include <fstream>

unsigned getCharOccurrences(std::ifstream& file, char c)
{
    unsigned count = 0;
    while (true)
    {
        char current = file.get();
        if (file.eof())
        {
            break;
        }
        if (current == c)
        {
            count++;
        }
    }
    return count;
}
unsigned getLinesCount(std::ifstream& file)
{
    return getCharOccurrences(file, '\n') + 1;
}

int main()
{
    std::ifstream file("Task1.cpp");
    if (!file.is_open())
    {
        return -1;
    }
    std::cout << getLinesCount(file);
}