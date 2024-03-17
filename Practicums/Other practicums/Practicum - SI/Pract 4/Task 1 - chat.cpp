#include <iostream>
#include <fstream>

struct User
{
    char name[25]{};
};
struct Message
{
    User from;
    char* text;
};

void printChat(std::ifstream& ifs)
{
    while (!ifs.eof())
    {
        Message result;
        ifs.read((char*)&result.from, sizeof(result.from));

        size_t size = 0;
        ifs.read((char*)&size, sizeof(size));

        result.text = new char[size + 1];
        ifs.read(result.text, size + 1);

        if (ifs.eof())
        {
            break;
        }
        std::cout << result.from.name << ": " << result.text << std::endl;
        delete[] result.text;
    }
}
void printChat(const char* filePath)
{
    if (!filePath)
    {
        return;
    }
    std::ifstream ifs(filePath, std::ios::binary);

    if (!ifs.is_open())
    {
        return;
    }

    printChat(ifs);
}
int main() 
{
    printChat("chat.dat");
}