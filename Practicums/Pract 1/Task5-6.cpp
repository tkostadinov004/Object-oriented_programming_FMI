#include <iostream>
using namespace std;

struct Point
{
	int x, y;
	void print()
	{
		cout << "(" << x << ", " << y << ")";
	}
};
struct Line
{
	Point first;
	Point second;
	double getDistance() const
	{
		int dx = first.x - second.x;
		int dy = first.y - second.y;
		return sqrt(dx * dx + dy * dy);
	}
	void printLength()
	{
		cout << getDistance() << endl;
	}
	bool isEquivalentTo(const Line& other)
	{
		return getDistance() == other.getDistance();
	}
	void printLine()
	{
		cout << "P1";
		first.print();
		cout << ", " << "P2";
		second.print();
		cout << " - ";
		printLength();
	}
};
int main()
{
	Point p1{ 1,2 };
	Point p2{ 3,-1 };
	Point p3{ 0,0 };
	Point p4{ 5,1 };
	Point p5{ 5,0 };
	Point p6{ 7,-3 };

	Line lines[3] = { {p1, p2}, {p3, p4}, {p5, p6} };

	for (size_t i = 0; i < 3; i++)
	{
		lines[i].printLine();
	}
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = i + 1; j < 3; j++)
		{
			cout << lines[i].isEquivalentTo(lines[j]) << endl;
		}
	}
}

