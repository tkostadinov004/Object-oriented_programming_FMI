#include <iostream>
#include <fstream>

int* getNumbers(size_t count)
{
    int* arr = new int[count];
    for (size_t i = 0; i < count; i++)
    {
        std::cin >> arr[i];
    }
    return arr;
}
void writeToFile(std::ofstream& ofs, const int* arr, size_t size)
{
    if (!arr)
    {
        return;
    }

    ofs.write((const char*)&size, sizeof(size));
    for (size_t i = 0; i < size; i++)
    {
        ofs.write((const char*)&arr[i], sizeof(arr[i]));
    }
}
void writeToFile(const char* filename)
{
    if (!filename)
    {
        return;
    }

    size_t count;
    std::cin >> count;

    int* arr = getNumbers(count);

    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs.is_open())
    {
        return;
    }
    writeToFile(ofs, arr, count);

    delete[] arr;
}
int main()
{
    writeToFile("nums.dat");
}