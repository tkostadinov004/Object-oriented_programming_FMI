#include <iostream>
using namespace std;

struct Polar
{
	double length, angle;
	void print()
	{
		cout << length << " V @ " << angle << " rad" << endl;
	}
};
struct Rect
{
	double x, y;
	void print()
	{
		cout << "(" << x << ", " << y << ")" << endl;
	}
};
Rect convertToRect(Polar vector)
{
	return { vector.length * cos(vector.angle), vector.length * sin(vector.angle) };
}
Polar convertToPolar(Rect vector)
{
	double radius = sqrt(vector.x * vector.x + vector.y * vector.y);

	return { radius,  asin(vector.y / radius) };
}
int main()
{
	{
		Polar p{ 20, 0.610865 }; //length - 20, 35 degrees = 0.61 rad
		p.print();

		Rect conv1 = convertToRect(p);
		conv1.print();

		convertToPolar(conv1).print();
	}
	cout << endl;
	{
		Rect vector{ sqrt(3), 1};
		vector.print();

		Polar polar = convertToPolar(vector);
		polar.print();
	}
}

