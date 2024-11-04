#include "BoundingBox.h"

BoundingBox::BoundingBox(const Vector3D& min, const Vector3D& max)
	: min(min), max(max)
{
}

bool BoundingBox::contains(const Vector3D& point) const
{
	return (point.x >= min.x && point.x <= max.x &&
		point.y >= min.y && point.y <= max.y &&
		point.z >= min.z && point.z <= max.z);
}
