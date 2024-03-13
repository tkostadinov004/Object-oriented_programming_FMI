#include <iostream>
#include <fstream>

void readFromFile(std::ifstream& ifs, int*& arr, size_t& size)
{
    ifs.read((char*)&size, sizeof(size));
    arr = new int[size];

    ifs.read((char*)arr, size * sizeof(arr));
}
void readFromFile(const char* filename, int*& arr, size_t& size)
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

    arr = nullptr;
    size = 0;
    readFromFile(ifs, arr, size);
}
int main()
{
    int* arr = nullptr;
    size_t size = 0;
    readFromFile("nums.dat", arr, size);
    
    for (size_t i = 0; i < size; i++)
    {
        std::cout << arr[i] << " ";
    }

    delete[] arr;
}