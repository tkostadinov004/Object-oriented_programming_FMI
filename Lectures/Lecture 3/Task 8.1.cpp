#include <iostream>

template <typename T>
//Possible types for T are those with a defined formatted input
void input(T* array, int n)
{
	if (!array)
	{
		return;
	}

	for (size_t i = 0; i < n; i++)
	{
		std::cin >> array[i];
	}
}

template <typename T>
//Possible types for T are those with a defined formatted output
void print(T* array, int n)
{
	if (!array)
	{
		return;
	}

	for (size_t i = 0; i < n; i++)
	{
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;
}
struct Student
{
	unsigned fn = 0;
};
int main() 
{
	constexpr size_t size = 5;
	{
		int arr[size]{};

		input(arr, size);
		print(arr, size);
	}
	{
		double arr[size]{};

		input(arr, size);
		print(arr, size);
	}
	{
		/*Student arr[size]{};

		input(arr, size);
		print(arr, size);*/
		//ERROR!!! - no known way to input a student
	}
}