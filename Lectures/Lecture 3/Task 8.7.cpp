#include <iostream>

struct S
{
	int a;
	int b;
	int c;
};
void sort(S* array, int n, bool (*compare)(const S&, const S&))
{
	if (!array)
	{
		return;
	}

	for (size_t i = 0; i < n; i++)
	{
		int minIndex = i;
		for (size_t j = i + 1; j < n; j++)
		{
			if (!compare(array[minIndex], array[j])) 
			{
				minIndex = j;
			}
		}
		if (minIndex != i)
		{
			std::swap(array[minIndex], array[i]);
		}
	}
}
void print(const S* array, int n)
{
	if (!array)
	{
		return;
	}

	for (size_t i = 0; i < n; i++)
	{
		std::cout << "a = " << array[i].a << "; b = " << array[i].b << "; c = " << array[i].c << std::endl;
	}
	std::cout << std::endl;
}
int main()
{
	constexpr size_t SIZE = 5;
	S arr[SIZE] = { {1,17,3},{2,1,-8}, {-1,-6,7}, {2,1,-9}, {6,-2,6} };
	{
		sort(arr, SIZE, [](const S& first, const S& second)
			{
				return first.a <= second.a;
			});
		print(arr, SIZE);
	}
	{
		sort(arr, SIZE, [](const S& first, const S& second)
			{
				return first.b <= second.b;
			});
		print(arr, SIZE);
	}
	{
		sort(arr, SIZE, [](const S& first, const S& second)
			{
				if (first.a == second.a)
				{
					if (first.b == second.b)
					{
						return first.c < second.c;
					}
					return first.b < second.b;
				}
				return first.a < second.a;
			});
		print(arr, SIZE);
	}
}