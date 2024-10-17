#include "Vector2D.h"

const Vector2D Vector2D::zeroes = Vector2D(0.0f, 0.0f);
const Vector2D Vector2D::ones = Vector2D(1.0f, 1.0f);

Vector2D::Vector2D()
	: x(0), y(0)
{
}

Vector2D::Vector2D(float x, float y)
	: x(x), y(y)
{
}

Vector2D::Vector2D(const Vector2D& vector)
	: x(vector.x), y(vector.y)
{
}

Vector2D Vector2D::lerp(const Vector2D& start, const Vector2D& end, float delta)
{
	Vector2D v;
	v.x = start.x * (1.0f - delta) + end.x * (delta);
	v.y = start.y * (1.0f - delta) + end.y * (delta);

	return v;
}

Vector2D Vector2D::operator+(const Vector2D& other) const
{
	return Vector2D(x + other.x, y + other.y);
}

Vector2D Vector2D::operator-(const Vector2D& other) const
{
	return Vector2D(x - other.x, y - other.y);
}

Vector2D Vector2D::operator*(float scalar) const
{
	return Vector2D(x * scalar, y * scalar);
}

Vector2D& Vector2D::operator+=(const Vector2D& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

Vector2D& Vector2D::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}

