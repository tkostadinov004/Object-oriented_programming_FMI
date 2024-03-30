#include "NumberSeries.h"
#include <iostream>

void NumberSeries::copyFrom(const NumberSeries& other)
{
    this->initialValue = other.initialValue;
    this->nums = new int[other.capacity];
    for (size_t i = 0; i < other.numsCount; i++)
    {
        this->nums[i] = other.nums[i];
    }
    this->numsCount = other.numsCount;
    this->capacity = other.capacity;
    this->transformer = other.transformer;
}

void NumberSeries::free()
{
    delete[] nums;
    nums = nullptr;
    numsCount = 0;
    capacity = 1;
}

void NumberSeries::grow()
{
    int* temp = new int[capacity *= 2];
    for (size_t i = 0; i < numsCount; i++)
    {
        temp[i] = nums[i];
    }
    delete[] nums;
    nums = temp;
}

NumberSeries::NumberSeries() = default;

NumberSeries::NumberSeries(int initialValue, TransformerFunction transformer)
{
    setInitialValue(initialValue);
    setTransformerFunction(transformer);
}

NumberSeries::NumberSeries(const NumberSeries& other)
{
    copyFrom(other);
}

NumberSeries::~NumberSeries()
{
    free();
}

NumberSeries& NumberSeries::operator=(const NumberSeries& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}
int NumberSeries::getNumber(int i)
{
    if (i == 0)
    {
        return initialValue;
    }

    while (numsCount <= i)
    {
        if (numsCount + 1 > capacity)
        {
            grow();
        }
        nums[numsCount++] = transformer(nums[numsCount - 1]);
    }

    return nums[i];
}

bool NumberSeries::isInSequence(int num) const
{
    for (size_t i = 0; i < numsCount; i++)
    {
        if (nums[i] == num)
        {
            return true;
        }
    }
    return false;
}

void NumberSeries::setInitialValue(int initialValue)
{
    free();
    this->initialValue = initialValue;
    this->nums = new int[1] {initialValue};
    this->numsCount = 1;
}

void NumberSeries::setTransformerFunction(TransformerFunction transformer)
{
    if (!transformer)
    {
        return;
    }
    free();
    this->transformer = transformer;
    this->nums = new int[1] {initialValue};
    this->numsCount = 1;
}
