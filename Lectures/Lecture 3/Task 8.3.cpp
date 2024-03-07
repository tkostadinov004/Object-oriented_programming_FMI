#include <iostream>

template <typename T>
//Possible types for T are those with a defined 'equal to' equivalence relation operator
bool member(T* array, int n, T x)
{
	if (!array)
	{
		return false;
	}

	for (size_t i = 0; i < n; i++)
	{
		if (array[i] == x)
		{
			return true;
		}
	}
	return false;
}

struct Student
{
	unsigned fn = 0;
};
int main() 
{
	constexpr size_t size = 5;
	{
		int arr[size] = {1,2,3,4,5};
		std::cout << member<int>(arr, size, 2) << std::endl;
		std::cout << member(arr, size, 2) << std::endl; //can be done without specifying the type too
		std::cout << member(arr, size, 7) << std::endl;
	}
	{
		char arr[size] = "Test";
		std::cout << member(arr, size, 'T') << std::endl;
		std::cout << member(arr, size, 'e') << std::endl;
		std::cout << member(arr, size, 'E') << std::endl;
	}
	{
		/*Student arr[size]{};
		std::cout << member(arr, size, {12345}) << std::endl;*/
		//ERROR!!! - no known way to compare students
	}
}