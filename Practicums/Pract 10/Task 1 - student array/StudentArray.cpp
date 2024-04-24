#include "StudentArray.h"
#include "HelperFunctions.h"

void StudentArray::copyFrom(const StudentArray& other)
{
    this->_capacity = other._capacity;
    this->_size = other._size;
    this->_data = new Student* [other._capacity] {nullptr};
    for (size_t i = 0; i < other._size; i++)
    {
        if (other._data[i])
        {
            this->_data[i] = new Student(*other._data[i]);
        }     
    }
}

void StudentArray::moveFrom(StudentArray&& other)
{
    this->_data = other._data;
    other._data = nullptr;
    this->_capacity = other._capacity;
    this->_size = other._size;
    other._capacity = other._size = 0;
}

void StudentArray::free()
{
    for (size_t i = 0; i < _size; i++)
    {
        delete _data[i];
    }
    delete[] _data;
    _data = nullptr;
    _size = 0;
}

void StudentArray::resize(size_t newCapacity)
{
    Student** temp = _data;
    _data = new Student* [newCapacity] {nullptr};
    for (size_t i = 0; i < _size; i++)
    {
        if (temp[i])
        {
            this->_data[i] = new Student(*temp[i]);
        }
    }
    delete[] temp;
    _capacity = newCapacity;
}

int StudentArray::getFirstFreeIndex() const
{
    for (size_t i = 0; i < _size; i++)
    {
        if (_data[i])
        {
            return i;
        }
    }
    return -1;
}

int StudentArray::getLastFreeIndex() const
{
    for (int i = _size - 1; i >= 0; i--)
    {
        if (_data[i])
        {
            return i;
        }
    }
    return -1;
}

StudentArray::StudentArray()
{
    _data = new Student* [_capacity] {nullptr};
}

StudentArray::StudentArray(const StudentArray& other)
{
    copyFrom(other);
}

StudentArray::StudentArray(StudentArray&& other)
{
    moveFrom(std::move(other));
}

StudentArray& StudentArray::operator=(const StudentArray& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

StudentArray& StudentArray::operator=(StudentArray&& other)
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

StudentArray::~StudentArray()
{
    free();
}

void StudentArray::push_front(const Student& student)
{
    if (_size + 1 > _capacity)
    {
        resize(std::max(2u, HelperFunctions::getNextPowerOfTwo(_capacity)));
    }
    for (int i = _size - 1; i >= 0; i--)
    {
        _data[i + 1] = _data[i];
    }
    _data[0] = new Student(student);
    _size++;
}

void StudentArray::push_front(Student&& student)
{
    if (_size + 1 > _capacity)
    {
        resize(std::max(2u, HelperFunctions::getNextPowerOfTwo(_capacity)));
    }
    for (int i = _size - 1; i >= 0; i--)
    {
        _data[i + 1] = _data[i];
    }
    _data[0] = new Student(std::move(student));
    _size++;
}

void StudentArray::push_back(const Student& student)
{
    if (_size + 1 > _capacity)
    {
        resize(std::max(2u, HelperFunctions::getNextPowerOfTwo(_capacity)));
    }
    _data[_size++] = new Student(student);
}

void StudentArray::push_back(Student&& student)
{
    if (_size + 1 > _capacity)
    {
        resize(std::max(2u, HelperFunctions::getNextPowerOfTwo(_capacity)));
    }
    _data[_size++] = new Student(std::move(student));
}

const Student& StudentArray::getFront() const
{
    int firstFreeIndex = getFirstFreeIndex();
    if (firstFreeIndex == -1)
    {
        throw std::logic_error("Array is empty!");
    }
    return *_data[firstFreeIndex];
}

const Student& StudentArray::getBack() const
{
    int lastFreeIndex = getLastFreeIndex();
    if (lastFreeIndex == -1)
    {
        throw std::logic_error("Array is empty!");
    }
    return *_data[lastFreeIndex];
}

size_t StudentArray::size() const
{
    return _size;
}

const Student& StudentArray::at(int index) const
{
    if (index < 0 || index >= _size || !_data[index])
    {
        throw std::logic_error("Invalid index!");
    }
    return *_data[index];
}

std::ostream& operator<<(std::ostream& os, const StudentArray& arr)
{
    for (size_t i = 0; i < arr._size; i++)
    {
        if (arr._data[i])
        {
            os << *arr._data[i] << std::endl;
        }
    }
    return os;
}
