#include "SchoolReport.h"

void SchoolReport::copyFrom(const SchoolReport& other)
{
    this->subjects = new Subject[other.subjectsCount];
    for (size_t i = 0; i < other.subjectsCount; i++)
    {
        this->subjects[i] = other.subjects[i];
    }
    this->subjectsCount = other.subjectsCount;
}

void SchoolReport::free()
{
    delete[] subjects;
    subjects = nullptr;
    subjectsCount = 0;
}

void SchoolReport::serializeSelf(std::ofstream& ofs) const
{
    ofs.write((const char*)&subjectsCount, sizeof(subjectsCount));
    for (size_t i = 0; i < subjectsCount; i++)
    {
        subjects[i].serializeSelf(ofs);
    }
}

void SchoolReport::deserializeSelf(std::ifstream& ifs)
{
    ifs.read((char*)&subjectsCount, sizeof(subjectsCount));
    this->subjects = new Subject[subjectsCount];
    for (size_t i = 0; i < subjectsCount; i++)
    {
        subjects[i].deserializeSelf(ifs);
    }
}

SchoolReport::SchoolReport() = default;

SchoolReport::SchoolReport(const Subject* subjects, size_t subjectsCount)
{
    setSubjects(subjects, subjectsCount);
}

SchoolReport::SchoolReport(const SchoolReport& other)
{
    copyFrom(other);
}

SchoolReport::~SchoolReport()
{
    free();
}

SchoolReport& SchoolReport::operator=(const SchoolReport& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

const Subject* SchoolReport::getSubjects() const
{
    return subjects;
}

size_t SchoolReport::getSubjectsCount() const
{
    return subjectsCount;
}

void SchoolReport::setSubjects(const Subject* subjects, size_t subjectsCount)
{
    if (!subjects || this->subjects == subjects)
    {
        return;
    }

    delete[] this->subjects;
    this->subjects = new Subject[subjectsCount];
    for (size_t i = 0; i < subjectsCount; i++)
    {
        this->subjects[i] = subjects[i];
    }
    this->subjectsCount = subjectsCount;
}

void SchoolReport::serializeSelf(const char* dest) const
{
    if (!dest)
    {
        return;
    }

    std::ofstream ofs(dest, std::ios::binary);
    if (!ofs.is_open())
    {
        return;
    }

    serializeSelf(ofs);
}

void SchoolReport::deserializeSelf(const char* src)
{
    if (!src)
    {
        return;
    }

    std::ifstream ifs(src, std::ios::binary);
    if (!ifs.is_open())
    {
        return;
    }

    deserializeSelf(ifs);
}

unsigned SchoolReport::getAverageGrade() const
{
    unsigned sum = 0;
    for (size_t i = 0; i < subjectsCount; i++)
    {
        sum += subjects[i].getAverageGrade();
    }
    return sum / subjectsCount;
}
