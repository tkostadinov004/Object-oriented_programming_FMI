#include <iostream>
using namespace std;

void popFront(int* arr, size_t& size)
{
	if (!arr)
	{
		return;
	}

	for (size_t i = 0; i < size - 1; i++)
	{
		arr[i] = arr[i + 1];
	}
	size--;
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
	size_t size = 5;

	int arr[] = { 1, 2, 3, 4, 5 };
	popFront(arr, size);
	printArray(arr, size);
}

