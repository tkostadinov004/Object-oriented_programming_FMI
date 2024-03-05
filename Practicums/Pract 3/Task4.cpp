#include <iostream>
#include <fstream>
#pragma warning (disable: 4996)

constexpr size_t BUFFER_SIZE = 1024;

char getUpper(char c)
{
    return c + 'A' - 'a';
}
char getLower(char c)
{
    return c + 'a' - 'A';
}
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
void transformLine(char* line, bool toCaps)
{
    if (!line)
    {
        return;
    }

    while (*line)
    {
        if (toCaps && islower(*line))
        {
            *line = getUpper(*line);
        }
        else if (!toCaps && isupper(*line))
        {
            *line = getLower(*line);
        }
        line++;
    }
}
void convertLettersCaseInFile(const char* fileName, bool toCaps)
{
    if (!fileName)
    {
        return;
    }
    const char* TEMP_FILE_NAME = "temp.txt";

    std::ifstream ifs(fileName);
    std::ofstream ofs(TEMP_FILE_NAME);

    if (!ifs.is_open() || !ofs.is_open())
    {
        return;
    }

    char buffer[BUFFER_SIZE];
    while (ifs.getline(buffer, BUFFER_SIZE))
    {
        transformLine(buffer, toCaps);
        ofs << buffer << std::endl;
    }
    copyFile(TEMP_FILE_NAME, fileName);
}

int main()
{
    {
        copyFile("Task4.cpp", "result.txt");
        convertLettersCaseInFile("result.txt", true);
    }
    {
        copyFile("Task4.cpp", "result.txt");
        convertLettersCaseInFile("result.txt", false);
    }
}