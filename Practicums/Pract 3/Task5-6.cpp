#include <iostream>
#include <fstream>
#pragma warning (disable: 4996)

constexpr size_t NAME_LENGTH = 64;

struct Person
{
    char name[NAME_LENGTH];
    bool gender;
    unsigned age;
};

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
void serializePerson(std::ofstream& ofs, const Person& person)
{
    ofs << person.name << " " << person.gender << " " << person.age << std::endl;
}
void serializeArray(const char* dest, const Person* arr, size_t size)
{
    if (!dest || !arr)
    {
        return;
    }
    std::ofstream ofs(dest);
    if (!ofs.is_open())
    {
        return;
    }

    for (size_t i = 0; i < size; i++)
    {
        serializePerson(ofs, arr[i]);
    }
}
Person deserializePerson(std::ifstream& ifs)
{
    Person person{};

    char nameBuffer[NAME_LENGTH];
    ifs >> nameBuffer;
    strcpy(person.name, nameBuffer);

    ifs >> person.gender >> person.age;
    ifs.ignore();

    return person;
}
Person* deserializeArray(const char* src, size_t& size)
{
    if (!src)
    {
        return nullptr;
    }

    std::ifstream ifs(src);
    if (!ifs.is_open())
    {
        return nullptr;
    }

    size = getLinesCount(ifs) - 1;
    ifs.clear();
    ifs.seekg(0);

    Person* arr = new Person[size];
    for (size_t i = 0; i < size; i++)
    {
        arr[i] = deserializePerson(ifs);
    }

    return arr;
}
int main()
{
    Person people[] = { {"Ivan", 0, 23}, {"Petar", 0, 18}, {"Petya", 1, 26} };
    serializeArray("people.txt", people, 3);

    size_t size = 0;
    Person* result = deserializeArray("people.txt", size);

    for (size_t i = 0; i < size; i++)
    {
        std::cout << result[i].name << " " << result[i].gender << " " << result[i].age << std::endl;
    }
}