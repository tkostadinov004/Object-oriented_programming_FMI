#include <iostream>
#include <fstream>
#include "Subject.h"
#pragma warning (disable: 4996)

void Subject::copyFrom(const Subject& other)
{
    this->name = new char[strlen(other.name) + 1];
    strcpy(this->name, other.name);

    this->grades = new unsigned[other.gradesCount];
    for (size_t i = 0; i < other.gradesCount; i++)
    {
        this->grades[i] = other.grades[i];
    }
    this->gradesCount = other.gradesCount;
}

void Subject::free()
{
    delete[] name;
    delete[] grades;

    name = nullptr;
    grades = nullptr;
    gradesCount = 0;
}

Subject::Subject() = default;

Subject::Subject(const char* name, const unsigned* grades, size_t gradesCount)
{
    setName(name);
    setGrades(grades, gradesCount);
}

Subject::Subject(const Subject& other)
{
    copyFrom(other);
}

Subject::~Subject()
{
    free();
}

Subject& Subject::operator=(const Subject& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }

    return *this;
}

const char* Subject::getName() const
{
    return name;
}

const unsigned* Subject::getGrades() const
{
    return grades;
}

size_t Subject::getGradesCount() const
{
    return gradesCount;
}

unsigned Subject::getAverageGrade() const
{
    unsigned sum = 0;
    for (size_t i = 0; i < gradesCount; i++)
    {
        sum += grades[i];
    }
    return sum / gradesCount;
}

void Subject::setName(const char* name)
{
    if (!name || this->name == name)
    {
        return;
    }

    delete[] this->name;
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

void Subject::setGrades(const unsigned* grades, size_t gradesCount)
{
    if (!grades || this->grades == grades)
    {
        return;
    }

    delete[] this->grades;
    this->grades = new unsigned[gradesCount];
    for (size_t i = 0; i < gradesCount; i++)
    {
        this->grades[i] = grades[i];
    }
    this->gradesCount = gradesCount;
}

void Subject::serializeSelf(std::ofstream& ofs)
{
    size_t namelen = strlen(name);
    ofs.write((const char*)&namelen, sizeof(namelen));
    ofs.write(name, namelen + 1);

    ofs.write((const char*)&gradesCount, sizeof(gradesCount));
    ofs.write((const char*)grades, sizeof(unsigned) * gradesCount);
}

void Subject::deserializeSelf(std::ifstream& ifs)
{
    size_t namelen = 0;
    ifs.read((char*)&namelen, sizeof(namelen));

    this->name = new char[namelen + 1];
    ifs.read(this->name, namelen + 1);

    ifs.read((char*)&gradesCount, sizeof(gradesCount));
    this->grades = new unsigned[gradesCount];
    ifs.read((char*)grades, sizeof(unsigned) * gradesCount);
}
