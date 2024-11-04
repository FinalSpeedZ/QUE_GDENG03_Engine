#pragma once

#include "Vector3D.h"

class BoundingBox
{
public:
	BoundingBox(const Vector3D& min, const Vector3D& max);
	~BoundingBox() {};

public:
	bool contains(const Vector3D& point) const;

public:
	Vector3D min;
	Vector3D max;
};

