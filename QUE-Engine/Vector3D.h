#pragma once

struct vec3;

class Vector3D
{
public:
	Vector3D();
	~Vector3D() {};

	Vector3D(float x);
	Vector3D(float x, float y, float z);
	Vector3D(const Vector3D& vector);
	Vector3D(vec3 vector);

	static Vector3D lerp(const Vector3D& start, const Vector3D& end, float delta);

	Vector3D operator+(const Vector3D& other) const;
	Vector3D operator-(const Vector3D& other) const;
	Vector3D& operator+=(const Vector3D& other);
	Vector3D& operator-=(const Vector3D& other);

	static const Vector3D zeroes;
	static const Vector3D ones;

public:
	float m_x, m_y, m_z;
};

