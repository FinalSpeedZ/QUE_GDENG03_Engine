#include "Point.h"

Point::Point()
	: x(0), y(0)
{
}

Point::Point(int x, int y)
	: x(x), y(y)
{
}

Point::Point(const Point& point)
	: x(point.x), y(point.y)
{
}
