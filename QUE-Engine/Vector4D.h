#pragma once

class Vector4D
{

public:
	Vector4D();
	~Vector4D() {};

	Vector4D(float x);
	Vector4D(float x, float y, float z, float w);
	Vector4D(const Vector4D& vector);

	static Vector4D lerp(const Vector4D& start, const Vector4D& end, float delta);
	void cross(Vector4D& v1, Vector4D& v2, Vector4D& v3);

	Vector4D operator+(const Vector4D& other) const;
	Vector4D operator-(const Vector4D& other) const;
	Vector4D operator*(float scalar) const;
	Vector4D& operator+=(const Vector4D& other);
	Vector4D& operator-=(const Vector4D& other);
	Vector4D& operator*=(float scalar);

	static const Vector4D zeroes;
	static const Vector4D ones;

public:
	float x, y, z, w;
};
