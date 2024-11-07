#pragma once

#include "Vector3D.h"

class BoundingBox
{
public:
	BoundingBox(const Vector3D& min, const Vector3D& max);
	~BoundingBox() {};

public:
	Vector3D min;
	Vector3D max;
};

