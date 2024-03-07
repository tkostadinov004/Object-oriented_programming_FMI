#include <iostream>

template <typename T>
//Possible types for T are those with a defined 'greater than or equal to' partial order relation operator, i.e. comparable types
bool ordered(T* array, int n)
{
	if (!array)
	{
		return false;
	}

	for (size_t i = 0; i < n - 1; i++)
	{
		if (array[i] >= array[i + 1])
		{
			return false;
		}
	}
	return true;
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
		std::cout << ordered<int>(arr, size) << std::endl;
		std::cout << ordered(arr, size) << std::endl; //can be done without specifying the type too
	}
	{
		char arr[size] = "Test";
		std::cout << ordered(arr, size) << std::endl;
	}
	{
		/*Student arr[size]{};
		std::cout << ordered(arr, size) << std::endl;*/
		//ERROR!!! - no known way to compare students
	}
}