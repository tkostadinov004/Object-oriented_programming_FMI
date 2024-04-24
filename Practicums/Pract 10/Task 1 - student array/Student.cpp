#include "Student.h"

Student::Student(const MyString& name, const MyString& fn, Major major)
{
    setName(name);
    setFN(fn);
    setMajor(major);
}

const MyString& Student::getName() const
{
    return name;
}

const MyString& Student::getFN() const
{
    return fn;
}

Major Student::getMajor() const
{
    return major;
}

void Student::setName(const MyString& name)
{
    if (name.empty())
    {
        throw std::invalid_argument("Name is empty!");
    }
    if (&name == &this->name)
    {
        return;
    }
    this->name = name;
}

void Student::setFN(const MyString& fn)
{
    if (fn.empty())
    {
        throw std::invalid_argument("Faculty number is empty!");
    }
    if (&fn == &this->fn)
    {
        return;
    }
    this->fn = fn;
}

void Student::setMajor(Major major)
{
    this->major = major;
}

std::ostream& operator<<(std::ostream& os, const Student& st)
{
    os << st.getName() << ", " << st.getFN() << ", " << (int)st.getMajor();
    return os;
}
