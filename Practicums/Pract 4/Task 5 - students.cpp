#include <iostream>
#include <fstream>

constexpr size_t MAX_STUDENTS_COUNT = 10;
constexpr size_t FN_LENGTH = 10;

enum class Major
{
    CS, IS, I, SI, M, AM, DA, STAT
};
void printMajorTitle(Major major)
{
    switch (major)
    {
        case Major::CS:
            std::cout << "Computer science";
            break;
        case Major::IS:
            std::cout << "Information systems";
            break;
        case Major::I:
            std::cout << "Informatics";
            break;
        case Major::SI:
            std::cout << "Software engineering";
            break;
        case Major::M:
            std::cout << "Mathematics";
            break;
        case Major::AM:
            std::cout << "Applied mathematics";
            break;
        case Major::DA:
            std::cout << "Data analysis";
            break;
        case Major::STAT:
            std::cout << "Statistics";
            break;
        default:
            std::cout << "Invalid major!";        
            break;
    }
}
enum class DegreeType
{
    Bacherors, Masters, PhD
};
void printDegreeType(DegreeType degreeType)
{
    switch (degreeType)
    {
        case DegreeType::Bacherors:
            std::cout << "Bachelor's";
            break;
        case DegreeType::Masters:
            std::cout << "Master's";
            break;
        case DegreeType::PhD:
            std::cout << "PhD";
            break;
        default:
            std::cout << "Invalid degree type!";
            break;
    }
}
enum class EducationType
{
    FullTime, PartTime
};
void printEducationType(EducationType educationType)
{
    switch (educationType)
    {
    case EducationType::FullTime:
        std::cout << "Full time";
        break;
    case EducationType::PartTime:
        std::cout << "Part time";
        break;
    default:
        std::cout << "Invalid education type!";
        break;
    }
}
struct Student
{
    char* name;
    char facultyNumber[FN_LENGTH + 1];
    Major major;
    DegreeType degreeType;
    EducationType educationType;
};
struct University
{
    char* name;
    Student students[MAX_STUDENTS_COUNT];
    size_t studentsCount = 0;
};
bool containsStudentByFN(const char* fn, const University& university)
{
    if (!fn)
    {
        return true;
    }

    for (size_t i = 0; i < university.studentsCount; i++)
    {
        if (strcmp(fn, university.students[i].facultyNumber) == 0)
        {
            return true;
        }
    }
    return false;
}
void addStudentToUniversity(const Student& student, University& university)
{
    if (containsStudentByFN(student.facultyNumber, university) || university.studentsCount + 1 >= MAX_STUDENTS_COUNT)
    {
        return;
    }

    university.students[university.studentsCount++] = student;
}
void serializeStudent(std::ofstream& ofs, const Student& student)
{
    size_t nameLength = strlen(student.name);
    ofs.write((const char*)&nameLength, sizeof(nameLength));
    ofs.write(student.name, nameLength + 1);

    ofs.write(student.facultyNumber, FN_LENGTH + 1);
    ofs.write((const char*)&student.major, sizeof(student.major));
    ofs.write((const char*)&student.educationType, sizeof(student.educationType));
    ofs.write((const char*)&student.degreeType, sizeof(student.degreeType));
}
void saveUniversityToFile(std::ofstream& ofs, const University& university)
{
    size_t nameLength = strlen(university.name);
    ofs.write((const char*)&nameLength, sizeof(nameLength));
    ofs.write(university.name, nameLength + 1);

    ofs.write((const char*)&university.studentsCount, sizeof(university.studentsCount));
    for (size_t i = 0; i < university.studentsCount; i++)
    {
        serializeStudent(ofs, university.students[i]);
    }
}void saveUniversityToFile(const char* filename, University& university)
{
    if (!filename)
    {
        return;
    }

    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs.is_open())
    {
        return;
    }

    saveUniversityToFile(ofs, university);
}
void deserializeStudent(std::ifstream& ifs, Student& student)
{
    size_t nameLength;
    ifs.read((char*)&nameLength, sizeof(nameLength));
    student.name = new char[nameLength + 1];
    ifs.read(student.name, nameLength + 1);

    ifs.read(student.facultyNumber, FN_LENGTH + 1);
    ifs.read((char*)&student.major, sizeof(student.major));
    ifs.read((char*)&student.educationType, sizeof(student.educationType));
    ifs.read((char*)&student.degreeType, sizeof(student.degreeType));
}
void loadUniversityFromFile(std::ifstream& ifs, University& university)
{
    size_t nameLength;
    ifs.read((char*)&nameLength, sizeof(nameLength));

    university.name = new char[nameLength + 1];
    ifs.read(university.name, nameLength + 1);

    ifs.read((char*)&university.studentsCount, sizeof(university.studentsCount));

    for (int i = 0; i < university.studentsCount; i++)
    {
        deserializeStudent(ifs, university.students[i]);
    }
}
void loadUniversityFromFile(const char* filename, University& university)
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

    loadUniversityFromFile(ifs, university);
}
void printStudent(const Student& student)
{
    std::cout << "Name: " << student.name << ", Faculty number: " << student.facultyNumber << ", Major: ";
    printMajorTitle(student.major);
    std::cout << ", Education type: "; 
    printEducationType(student.educationType);
    std::cout << ", Degree type: "; 
    printDegreeType(student.degreeType);
    std::cout << std::endl;
}
void printUniversityStudents(const University& university)
{
    for (size_t i = 0; i < university.studentsCount; i++)
    {
        printStudent(university.students[i]);
    }
}
void freeMemory(University& university)
{
    delete[] university.name;
    for (size_t i = 0; i < university.studentsCount; i++)
    {
        delete[] university.students[i].name;
    }
}
int main()
{
    //University uni{ new char[10] {"SU"}, {{new char[10] {"Ivan"}, "1111111111", Major::IS, DegreeType::Bacherors, EducationType::FullTime}, {new char[10] {"Georgi"}, "2222222222", Major::M, DegreeType::Masters, EducationType::PartTime}}, 2 };
    //saveUniversityToFile("uni.dat", uni);

    University uni{};
    loadUniversityFromFile("uni.dat", uni);

    std::cout << "University name: " << uni.name << std::endl;
    printUniversityStudents(uni);
}