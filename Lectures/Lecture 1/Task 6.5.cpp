#include <iostream>
using namespace std;

struct Point
{
	double x, y;
	void print() const
	{
		cout << "(" << x << ", " << y << ")" << endl;
	}
};
void sort(Point* arr, size_t size)
{
	if (!arr)
	{
		return;
	}

	for (size_t i = 0; i < size; i++)
	{
		int minIndex = i;
		for (size_t j = i + 1; j < size; j++)
		{
			if (arr[j].x < arr[minIndex].x)
			{
				minIndex = j;
			}
			else if (arr[j].x == arr[minIndex].x && arr[j].y < arr[minIndex].y)
			{
				minIndex = j;
			}
		}
		if (minIndex != i)
		{
			swap(arr[i], arr[minIndex]);
		}
	}
}
void printPoints(const Point* arr, size_t size)
{
	if (!arr)
	{
		return;
	}
	for (size_t i = 0; i < size; i++)
	{
		arr[i].print();
	}
}
int main()
{
	constexpr size_t SIZE = 6;
	Point points[SIZE] = { {3, -4}, {1,6}, {3,-5}, {2,2}, {1,0}, {6,9} };

	sort(points, SIZE);
	printPoints(points, SIZE);
}

