#pragma once
#include <iostream>

constexpr unsigned BUCKET_SIZE = sizeof(uint8_t) * 8;
constexpr unsigned ELEMENTS_PER_BUCKET = BUCKET_SIZE / 2;
class MultiSet
{
	uint8_t* buckets = nullptr;
	size_t bucketsCount = 0;
	size_t upperBound = 0;
	void copyFrom(const MultiSet& other);
	void free();
	unsigned getBucketIndex(int n) const;
	unsigned getEndIndexInBucket(int n) const;
public:
	MultiSet();
	MultiSet(size_t upperBound);
	MultiSet(const MultiSet& other);
	~MultiSet();
	MultiSet& operator=(const MultiSet& other);

	void add(int n);
	void remove(int n);
	unsigned getCount(int n) const;
	void print() const;
	friend MultiSet getUnion(const MultiSet& first, const MultiSet& second);
	friend MultiSet getIntersection(const MultiSet& first, const MultiSet& second);
};