#include <iostream>
#include <fstream>
#pragma warning (disable: 4996)

constexpr size_t BUFFER_SIZE = 1024;

void copyFile(const char* source_filename, const char* destination_filename)
{
    if (!source_filename || !destination_filename)
    {
        return;
    }

    std::ifstream src(source_filename);
    std::ofstream dest(destination_filename);

    if (!src.is_open() || !dest.is_open())
    {
        return;
    }

    char buffer[BUFFER_SIZE];
    while (!src.eof())
    {
        src.getline(buffer, BUFFER_SIZE);
        dest << buffer << std::endl;
    }
}

int main()
{
    copyFile("Task2.cpp", "result.txt");
}