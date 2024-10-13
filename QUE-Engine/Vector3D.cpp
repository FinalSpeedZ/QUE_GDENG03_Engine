#include "Vector3D.h"

#include "Vertex.h"

const Vector3D Vector3D::zeroes = Vector3D(0.0f, 0.0f, 0.0f);
const Vector3D Vector3D::ones = Vector3D(1.0f, 1.0f, 1.0f);

Vector3D::Vector3D()
	: m_x(0), m_y(0), m_z(0)
{
}

Vector3D::Vector3D(float x)
	: m_x(x), m_y(x), m_z(x)
{
}

Vector3D::Vector3D(float x, float y, float z)
	: m_x(x), m_y(y), m_z(z)
{
}

Vector3D::Vector3D(const Vector3D& vector)
	: m_x(vector.m_x), m_y(vector.m_y), m_z(vector.m_z)
{
}

Vector3D Vector3D::lerp(const Vector3D& start, const Vector3D& end, float delta)
{
	Vector3D v;
	v.m_x = start.m_x * (1.0f - delta) + end.m_x * (delta);
	v.m_y = start.m_y * (1.0f - delta) + end.m_y * (delta);
	v.m_z = start.m_z * (1.0f - delta) + end.m_z * (delta);

	return v;
}

Vector3D Vector3D::operator+(const Vector3D& other) const
{
    return Vector3D(m_x + other.m_x, m_y + other.m_y, m_z + other.m_z);
}

Vector3D Vector3D::operator-(const Vector3D& other) const
{
    return Vector3D(m_x - other.m_x, m_y - other.m_y, m_z - other.m_z);
}

Vector3D& Vector3D::operator+=(const Vector3D& other)
{
    m_x += other.m_x;
    m_y += other.m_y;
    m_z += other.m_z;
    return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D& other)
{
    m_x -= other.m_x;
    m_y -= other.m_y;
    m_z -= other.m_z;
    return *this;
}