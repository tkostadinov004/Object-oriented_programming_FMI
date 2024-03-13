#include <iostream>
#include <fstream>

void replace(std::fstream& fs, char oldChar, char newChar)
{
    while (!fs.eof())
    {
        if (fs.get() == oldChar)
        {
            fs.seekp(-1, std::ios::cur);
            fs << newChar;
        }
        fs.flush();
    }
}
int main()
{
    std::fstream fs("message.txt", std::ios::in | std::ios::out);
    if (!fs.is_open())
    {
        return -1;
    }

    replace(fs, 'a', 'd');
}