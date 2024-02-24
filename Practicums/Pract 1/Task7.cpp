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
struct Triangle
{
	Line a, b, c;
	bool isValid()
	{
		double l1 = a.getDistance();
		double l2 = b.getDistance();
		double l3 = c.getDistance();
		return l1 > 0 && l2 > 0 && l3 > 0 && l1 + l2 > l3 && l1 + l3 > l2 && l2 + l3 > l1;
	}
	double getPerimeter()
	{
		return a.getDistance() + b.getDistance() + c.getDistance();
	}
	double getArea()
	{
		double halfPerimeter = getPerimeter() / 2;
		double l1 = a.getDistance();
		double l2 = b.getDistance();
		double l3 = c.getDistance();
		return sqrt(halfPerimeter * (halfPerimeter - l1) * (halfPerimeter - l2) * (halfPerimeter - l3));
	}
	void print()
	{
		a.printLine();
		b.printLine();
		c.printLine();

		if (isValid())
		{
			cout << "Perimeter = " << getPerimeter() << ", Area = " << getArea() << endl;
		}
		else
		{
			cout << "Invalid triangle!" << endl;
		}
	}
};
int main()
{
	Triangle t1{ {{1,2}, {2,3}}, {{0,0},{3, -1}}, {{1,1}, {5,0}} };
	t1.print();
	
	cout << endl;

	Triangle t2{ {{1,2}, {2,3}}, {{0,0},{3, -1}}, {{1,1}, {5,5}} };
	t2.print();
}

