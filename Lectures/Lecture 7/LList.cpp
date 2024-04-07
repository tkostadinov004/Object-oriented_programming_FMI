#include <iostream>
#include "LList.h"

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
LList<T>::LList(int x, int y)
{
	for (size_t i = x; i <= y; i++)
	{
		push_back(i);
	}
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
	head = new Box(value, head);
}

template<typename T>
void LList<T>::pop()
{
	if (head != nullptr)
	{
		head = head->next;
	}
}

template<typename T>
void LList<T>::push_back(const T& value)
{
	if (!head)
	{
		head = new Box(value, nullptr);
		return;
	}

	Box* temp = head;
	while (temp->next != nullptr)
	{
		temp = temp->next;
	}
	temp->next = new Box(value, nullptr);
}

template<typename T>
T& LList<T>::get_ith(size_t index)
{
	Box* box = locate(index);
	T res = T();
	return box ? box->data : res;
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
		temp = temp->next;
	}
	return elementCount;
}

template<typename T>
void LList<T>::removeAll(const T& value)
{
	if (head == nullptr)
	{
		return;
	}
	if (head->data == value)
	{
		head = head->next;
	}

	Box* temp = head;
	while (temp != nullptr)
	{
		if (temp->next && temp->next->data == value)
		{
			temp->next =  temp->next->next;
		}
		if (!temp->next && temp->data == value)
		{
			head = head->next;
			break;
		}
		temp = temp->next;
	}
}

template<typename T>
void LList<T>::append(const LList<T>& list)
{
	Box* list_pred = list.head;
	if (!list_pred)
	{
		return;
	}

	if (!head)
	{
		head = new Box(list_pred->data, nullptr);
		list_pred = list_pred->next;
	}
	Box* this_pred = head;

	while (this_pred != nullptr && this_pred->next != nullptr)
	{
		this_pred = this_pred->next;
	}
	while (list_pred != nullptr)
	{
		this_pred->next = new Box(list_pred->data, nullptr);
		this_pred = this_pred->next;
		list_pred = list_pred->next;
	}
}

template<typename T>
LList<T> LList<T>::concat(const LList<T>& list) const
{
	LList<T> result(*this);
	result.append(list);
	return result;
}

template<typename T>
LList<T>& LList<T>::operator+=(const T& value)
{
	push_back(value);
	return *this;
}

template<typename T>
LList<T>& LList<T>::operator+=(const LList<T>& list)
{
	append(list);
	return *this;
}

template<typename T>
LList<T> LList<T>::operator+(const LList<T>& list) const
{
	return concat(list);
}

template<typename T>
const T& LList<T>::operator[](int index) const
{
	return get_ith(index);
}

template<typename T>
T& LList<T>::operator[](int index)
{
	return get_ith(index);
}

template<typename T>
void LList<T>::reverse()
{
	Box* prev = nullptr;
	Box* curr = head;
	while (curr != nullptr)
	{
		Box* temp = curr->next;
		curr->next = prev;
		prev = curr;
		curr = temp;
	}
	head = prev;
}

template<typename T>
LList<T> LList<T>::mapF(T(*func)(const T&)) const
{
	if (!head)
	{
		return LList<T>();
	}
	Box* curr = this->head;

	LList<T> result;
	result.head = new Box(func(curr->data), nullptr);
	curr = curr->next;

	Box* result_temp = result.head;
	while (curr != nullptr)
	{
		result_temp->next = new Box(func(curr->data), nullptr);
		result_temp = result_temp->next;
		curr = curr->next;
	}
	return result;
}

template<typename T>
LList<T>& LList<T>::mapD(T(*func)(const T&))
{
	Box* temp = head;
	while (temp != nullptr)
	{
		temp->data = func(temp->data);
		temp = temp->next;
	}
	return *this;
}

template<typename T>
T LList<T>::reduce(T(*func)(const T& accumulator, const T& currentValue), const T& initialValue) const
{
	T result = initialValue;
	Box* temp = head;

	while (temp != nullptr)
	{
		result = func(result, temp->data);
		temp = temp->next;
	}
	return result;
}