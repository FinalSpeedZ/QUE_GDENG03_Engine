#include "Vector4D.h"

const Vector4D Vector4D::zeroes = Vector4D(0.0f, 0.0f, 0.0f, 0.0f);
const Vector4D Vector4D::ones = Vector4D(1.0f, 1.0f, 1.0f, 1.0f);

Vector4D::Vector4D()
	: x(0), y(0), z(0), w(0)
{
}

Vector4D::Vector4D(float x)
	: x(x), y(x), z(x), w(x)
{
}

Vector4D::Vector4D(float x, float y, float z, float w)
	: x(x), y(y), z(z), w(w)
{
}

Vector4D::Vector4D(const Vector4D& vector)
	: x(vector.x), y(vector.y), z(vector.z), w(vector.w)
{
}

Vector4D Vector4D::lerp(const Vector4D& start, const Vector4D& end, float delta)
{
	Vector4D v;
	v.x = start.x * (1.0f - delta) + end.x * (delta);
	v.y = start.y * (1.0f - delta) + end.y * (delta);
	v.z = start.z * (1.0f - delta) + end.z * (delta);
	v.w = start.w * (1.0f - delta) + end.w * (delta);

	return v;
}

Vector4D Vector4D::operator+(const Vector4D& other) const
{
	return Vector4D(x + other.x, y + other.y, z + other.z, w + other.w);
}

Vector4D Vector4D::operator-(const Vector4D& other) const
{
	return Vector4D(x - other.x, y - other.y, z - other.z, w - other.w);
}

Vector4D Vector4D::operator*(float scalar) const
{
	return Vector4D(x * scalar, y * scalar, z * scalar, w * scalar);
}

Vector4D& Vector4D::operator+=(const Vector4D& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;
	return *this;
}

Vector4D& Vector4D::operator-=(const Vector4D& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	w -= other.w;
	return *this;
}

Vector4D& Vector4D::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;
	return *this;
}
