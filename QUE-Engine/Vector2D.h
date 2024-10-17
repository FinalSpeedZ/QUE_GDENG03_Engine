#pragma once
class Vector2D
{

public:
	Vector2D();
	~Vector2D() {};

	Vector2D(float x, float y);
	Vector2D(const Vector2D& vector);

	static Vector2D lerp(const Vector2D& start, const Vector2D& end, float delta);

	Vector2D operator+(const Vector2D& other) const;
	Vector2D operator-(const Vector2D& other) const;
	Vector2D operator*(float scalar) const;
	Vector2D& operator+=(const Vector2D& other);
	Vector2D& operator-=(const Vector2D& other);
	Vector2D& operator*=(float scalar);

	static const Vector2D zeroes;
	static const Vector2D ones;

public:
	float x, y;
};

