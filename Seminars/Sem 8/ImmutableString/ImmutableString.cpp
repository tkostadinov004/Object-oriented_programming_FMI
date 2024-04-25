#include "ImmutableString.h"
#include <string.h>
StringPool ImmutableString::_pool;

void ImmutableString::copyFrom(const ImmutableString& other)
{
    _data = _pool.getAllocatedString(other._data);
}

void ImmutableString::free()
{
    _pool.freeString(_data);
    _data = nullptr;
}

ImmutableString::ImmutableString(const char* str)
{
    _data = _pool.getAllocatedString(str);
}

ImmutableString::ImmutableString(const ImmutableString& other)
{
    copyFrom(other);
}

ImmutableString& ImmutableString::operator=(const ImmutableString& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

ImmutableString::~ImmutableString()
{
    free();
}

char ImmutableString::operator[](int index) const
{
    return _data[index];
}

const char* ImmutableString::c_str() const
{
    return _data;
}

size_t ImmutableString::length() const
{
    return strlen(_data);
}
