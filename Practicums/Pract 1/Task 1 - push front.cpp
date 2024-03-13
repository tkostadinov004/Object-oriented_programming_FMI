#include <iostream>
using namespace std;

void grow(int*& arr, size_t& capacity)
{
	int* temp = new int[capacity * 2];
	for (size_t i = 0; i < capacity; i++)
	{
		temp[i] = arr[i];
	}
	delete[] arr;

	capacity *= 2;
	arr = temp;
}
void pushFront(int*& arr, size_t& capacity, size_t& size, int num)
{
	if (!arr)
	{
		return;
	}

	if (capacity == size)
	{
		grow(arr, capacity);
	}
	for (int i = size; i > 0; i--)
	{
		arr[i] = arr[i - 1];
	}
	arr[0] = num;
	size++;
}
void printArray(const int* arr, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}
}
int main()
{
	size_t capacity = 5, size = 5;
	int num = 6;

	int* arr = new int[capacity]{ 1,2,3,4,5 };
	pushFront(arr, capacity, size, num);
	printArray(arr, size);

	delete[] arr;
}

