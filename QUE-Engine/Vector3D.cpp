#include "Vector3D.h"

#include "Vertex.h"

#include <cmath>

const Vector3D Vector3D::zeroes = Vector3D(0.0f, 0.0f, 0.0f);
const Vector3D Vector3D::ones = Vector3D(1.0f, 1.0f, 1.0f);

Vector3D::Vector3D()
	: x(0), y(0), z(0)
{
}

Vector3D::Vector3D(float x)
	: x(x), y(x), z(x)
{
}

Vector3D::Vector3D(float x, float y, float z)
	: x(x), y(y), z(z)
{
}

Vector3D::Vector3D(const Vector3D& vector)
	: x(vector.x), y(vector.y), z(vector.z)
{
}

Vector3D Vector3D::lerp(const Vector3D& start, const Vector3D& end, float delta)
{
	Vector3D v;
	v.x = start.x * (1.0f - delta) + end.x * (delta);
	v.y = start.y * (1.0f - delta) + end.y * (delta);
	v.z = start.z * (1.0f - delta) + end.z * (delta);

	return v;
}

Vector3D Vector3D::operator+(const Vector3D& other) const
{
    return Vector3D(x + other.x, y + other.y, z + other.z);
}

Vector3D Vector3D::operator-(const Vector3D& other) const
{
    return Vector3D(x - other.x, y - other.y, z - other.z);
}

Vector3D Vector3D::operator*(float scalar) const
{
    return Vector3D(x * scalar, y * scalar, z * scalar);
}

Vector3D& Vector3D::operator+=(const Vector3D& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vector3D& Vector3D::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Vector3D Vector3D::normalize() const
{
    float len = length();
    return Vector3D(x / len, y / len, z / len);
}

Vector3D Vector3D::cross(const Vector3D& other) const
{
    return Vector3D(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

float Vector3D::dot(const Vector3D& other) const
{
    return x * other.x + y * other.y + z * other.z;
}

float Vector3D::length() const
{
    return std::sqrt(x * x + y * y + z * z);
}
