#include <iostream>
#include "LList.h"

int main()
{
	LList<int> list;
	list.push(3);
	list.push(2);
	list.push(1);
	list.print();

	LList<int> list2(list);
	list2.insertAt(3, 5);

	list.print();
	list2.print();
}
template<typename T>
LList<T>::Box::Box(const T& value, Box* next) : data(value), next(next) {}

template<typename T>
void LList<T>::copyFrom(const LList<T>& other)
{
	Box* otherPtr = other.head;
	if (!otherPtr)
	{
		this->head = nullptr;
		return;
	}

	this->head = new Box(otherPtr->data, nullptr);
	otherPtr = otherPtr->next;

	Box* temp = head;
	while (otherPtr != nullptr)
	{
		temp->next = new Box(otherPtr->data, nullptr);
		otherPtr = otherPtr->next;
		temp = temp->next;
	}
}

template<typename T>
void LList<T>::free()
{
	while (this->head != nullptr)
	{
		Box* next = this->head->next;
		delete[] this->head;
		this->head = next;
	}
	this->head = nullptr;
}

template<typename T>
typename LList<T>::Box* LList<T>::locate(size_t index)
{
	Box* temp = head;
	for (size_t i = 0; i < index; i++)
	{
		if (temp == nullptr)
		{
			return nullptr;
		}
		temp = temp->next;
	}
	return temp;
}

template<typename T>
LList<T>::LList(const LList<T>& other)
{
	copyFrom(other);
}

template<typename T>
LList<T>& LList<T>::operator=(const LList<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
LList<T>::~LList()
{
	free();
}

template<typename T>
void LList<T>::push(const T& value)
{
	/*Box* temp = head;
	while (temp->next != nullptr)
	{
		temp = temp->next;
	}
	temp->next = new Box(value, nullptr);*/
	head = new Box(value, head);
}

template<typename T>
void LList<T>::pop()
{
	/*Box* temp = head;
	while (temp->next != nullptr)
	{
		temp = temp->next;
	}
	temp->next = nullptr;*/
	if (head != nullptr)
	{
		head = head->next;
	}
}

template<typename T>
void LList<T>::insertAt(size_t index, const T& value)
{
	if (index == 0)
	{
		head = new Box(value, head);
		return;
	}

	Box* prev = locate(index - 1);
	if (!prev)
	{
		return;
	}
	prev->next = new Box(value, prev->next);
}

template<typename T>
void LList<T>::deleteAt(size_t index)
{
	if (index == 0 && head)
	{
		head = head->next;
		return;
	}

	Box* prev = locate(index - 1);
	if (!prev)
	{
		return;
	}

	prev->next = prev->next->next;
}

template<typename T>
void LList<T>::print() const
{
	Box* temp = head;
	while (temp != nullptr)
	{
		std::cout << temp->data << " ";
		temp = temp->next;
	}
	std::cout << std::endl;
}

template<typename T>
size_t LList<T>::count(int x) const
{
	size_t elementCount = 0;
	Box* temp = head;
	while (temp != nullptr)
	{
		if (temp->data == x)
		{
			elementCount++;
		}
	}
	return elementCount;
}
