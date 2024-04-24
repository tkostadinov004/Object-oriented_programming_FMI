#pragma once
#include "Student.h"

class StudentArray
{
	Student** _data = nullptr;
	size_t _size = 0;
	size_t _capacity = 2;

	void copyFrom(const StudentArray& other);
	void moveFrom(StudentArray&& other);
	void free();
	void resize(size_t newCapacity);

	int getFirstFreeIndex() const;
	int getLastFreeIndex() const;
public:
	StudentArray();
	StudentArray(const StudentArray& other);
	StudentArray(StudentArray&& other);
	StudentArray& operator=(const StudentArray& other);
	StudentArray& operator=(StudentArray&& other);
	~StudentArray();

	void push_front(const Student& student);
	void push_front(Student&& student);
	void push_back(const Student& student);
	void push_back(Student&& student);

	const Student& getFront() const;
	const Student& getBack() const;
	size_t size() const;
	const Student& at(int index) const;
	friend std::ostream& operator<<(std::ostream& os, const StudentArray& arr);
};