#pragma once


class Point
{
public:
	Point();
	~Point() {};

	Point(int x, int y);
	Point(const Point& point);

public:
	int x;
	int y;

};

