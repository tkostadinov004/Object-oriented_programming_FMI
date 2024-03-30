#include "MultiSet.h"
#include <cmath>

void MultiSet::copyFrom(const MultiSet& other)
{
	this->bucketsCount = other.bucketsCount;
	this->buckets = new uint8_t[other.bucketsCount]{ 0 };
	this->upperBound = other.upperBound;
}

void MultiSet::free()
{
	delete[] buckets;
	bucketsCount = 0;
	buckets = nullptr;
}

unsigned MultiSet::getBucketIndex(int n) const
{
	return n / ELEMENTS_PER_BUCKET;
}

unsigned MultiSet::getEndIndexInBucket(int n) const
{
	return 2 * (n % ELEMENTS_PER_BUCKET);
}

MultiSet::MultiSet() = default;
MultiSet::MultiSet(size_t upperBound)
{
	this->bucketsCount = upperBound / ELEMENTS_PER_BUCKET + 1;
	this->buckets = new uint8_t[bucketsCount]{ 0 };
	this->upperBound = upperBound;
}
MultiSet::MultiSet(const MultiSet& other)
{
	copyFrom(other);
}
MultiSet::~MultiSet()
{
	free();
}

MultiSet& MultiSet::operator=(const MultiSet& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

void MultiSet::add(int n)
{
	if ((n < 0 || n >= upperBound) || getCount(n) >= 3)
	{
		return;
	}

	int bucketIndex = getBucketIndex(n);
	int end = getEndIndexInBucket(n);

	buckets[bucketIndex] += (1 << end);
}

void MultiSet::remove(int n)
{
	if (getCount(n) == 0)
	{
		return;
	}

	int bucketIndex = getBucketIndex(n);
	int end = getEndIndexInBucket(n);

	buckets[bucketIndex] -= (1 << end);
}

unsigned MultiSet::getCount(int n) const
{
	int bucketIndex = getBucketIndex(n);
	int end = getEndIndexInBucket(n);

	return (buckets[bucketIndex] & (3 << end)) >> end;
}

void MultiSet::print() const
{
	std::cout << "{ ";
	for (size_t i = 0; i < upperBound; i++)
	{
		if (getCount(i) > 0)
		{
			std::cout << i << "(" << getCount(i) << "), ";
		}
	}
	std::cout << "}" << std::endl;
}

MultiSet getUnion(const MultiSet& first, const MultiSet& second)
{
	const MultiSet& smaller = first.bucketsCount <= second.bucketsCount ? first : second;
	const MultiSet& bigger = first.bucketsCount > second.bucketsCount ? first : second;

	MultiSet result(bigger.upperBound);
	for (size_t i = 0; i < smaller.upperBound; i++)
	{
		int occs = std::max(smaller.getCount(i), bigger.getCount(i));
		int bucketIndex = result.getBucketIndex(i);
		int indexInBucket = result.getEndIndexInBucket(i);
		result.buckets[bucketIndex] += (occs << indexInBucket);
	}

	for (size_t i = smaller.bucketsCount; i < bigger.bucketsCount; i++)
	{
		result.buckets[i] = bigger.buckets[i];
	}
	return result;
}

MultiSet getIntersection(const MultiSet& first, const MultiSet& second)
{
	const MultiSet& smaller = first.bucketsCount <= second.bucketsCount ? first : second;
	const MultiSet& bigger = first.bucketsCount > second.bucketsCount ? first : second;

	MultiSet result(smaller.upperBound);
	for (size_t i = 0; i < smaller.upperBound; i++)
	{
		int occs = std::min(smaller.getCount(i), bigger.getCount(i));
		int bucketIndex = result.getBucketIndex(i);
		int indexInBucket = result.getEndIndexInBucket(i);
		result.buckets[bucketIndex] += (occs << indexInBucket);
	}
	return result;
}
