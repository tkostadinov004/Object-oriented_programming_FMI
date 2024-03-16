#include <iostream>
#include <fstream>

struct Point
{
	double x;
	double y;
};
struct Line
{
	Point first;
	Point second;
	double getSlope() const
	{
		return (second.y - first.y) / (second.x - first.x);
	}
	double getYIntercept() const
	{
		return first.y - this->getSlope() * first.x;
	}
	bool operator||(const Line& other) const //isParralelTo
	{
		return this->getSlope() == other.getSlope();
	}
	bool isPointOnLine(const Point& point) const
	{
		int slope = this->getSlope();
		int yIntercept = first.y - slope * first.x;
		return point.y == slope * point.x + yIntercept;
	}
	Point operator*(const Line& other) const //findIntersectionWith
	{
		Point intersection;
		intersection.x = (other.getYIntercept() - this->getYIntercept()) / (this->getSlope() - other.getSlope());
		intersection.y = other.getSlope() * intersection.x + other.getYIntercept();
		return intersection;
	}
	Line getAngleBisectorWith(const Line& other) const
	{
		float thisSlope = this->getSlope();
		float otherSlope = other.getSlope();

		double steeperSlope = abs(thisSlope) > abs(otherSlope) ? thisSlope : otherSlope;
		double smallerSlope = steeperSlope == thisSlope ? otherSlope : thisSlope;

		double angle = atan((steeperSlope - smallerSlope) / (1 + steeperSlope * smallerSlope));
		double halfAngleTan = tan(angle / 2);

		Point intersection = (*this) * other;
		double bisectorSlope = (steeperSlope - halfAngleTan) / (1 + (steeperSlope * halfAngleTan));
		if (tan(angle) > 0)
		{
			bisectorSlope = -1 / bisectorSlope;
		}

		double bisectorYIntercept = intersection.y - bisectorSlope * intersection.x;

		Line bisector;
		bisector.first.x = 1;
		bisector.first.y = bisectorSlope * bisector.first.x + bisectorYIntercept;

		bisector.second.x = 3;
		bisector.second.y = bisectorSlope * bisector.second.x + bisectorYIntercept;

		return bisector;
	}
};
int main()
{
	{
		Line l1{ {4, 3.75}, {8, 6.75} };
		Line l2{ {5, 11.8}, {10, 23.8} };

		std::cout << l1.getSlope() << std::endl;
		std::cout << l2.getSlope() << std::endl;

		std::cout << l1.getYIntercept() << std::endl;
		std::cout << l2.getYIntercept() << std::endl;

		Point intersection = l1 * l2;
		std::cout << intersection.x << " " << intersection.y << std::endl;

		Line bisector = l1.getAngleBisectorWith(l2);
		std::cout << bisector.getSlope() << std::endl;
		std::cout << bisector.getYIntercept() << std::endl;
	}
}