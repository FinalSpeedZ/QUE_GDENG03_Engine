#include "Ray.h"

#include <algorithm>
#include <iostream>


Ray::Ray(const Vector3D& origin, const Vector3D& direction)
	: origin(origin)
{
    this->direction = direction.normalize();
}

bool Ray::intersects(const BoundingBox& box, float& t) const
{
    const Vector3D& min = box.min;
    const Vector3D& max = box.max;

    // Check for Zero Division
    float invX, invY, invZ;
    if (direction.x != 0) 
    {
        invX = 1.0f / direction.x;
    }
    else 
    {
        invX = 0;
    }

    if (direction.y != 0) 
    {
        invY = 1.0f / direction.y;
    }
    else 
    {
        invY = 0;
    }

    if (direction.z != 0) 
    {
        invZ = 1.0f / direction.z;
    }
    else 
    {
        invZ = 0;
    }

    Vector3D invDir(invX, invY, invZ);

    float t0[3], t1[3];

    // Calculate t values for box min and max corners
    if (direction.x != 0) 
    {
        t0[0] = (min.x - origin.x) * invDir.x;
        t1[0] = (max.x - origin.x) * invDir.x;
    }
    else 
    {
        t0[0] = -std::numeric_limits<float>::infinity();
        t1[0] = std::numeric_limits<float>::infinity();
    }

    if (direction.y != 0) 
    {
        t0[1] = (min.y - origin.y) * invDir.y;
        t1[1] = (max.y - origin.y) * invDir.y;
    }
    else 
    {
        t0[1] = -std::numeric_limits<float>::infinity();
        t1[1] = std::numeric_limits<float>::infinity();
    }

    if (direction.z != 0) 
    {
        t0[2] = (min.z - origin.z) * invDir.z;
        t1[2] = (max.z - origin.z) * invDir.z;
    }
    else
    {
        t0[2] = -std::numeric_limits<float>::infinity();
        t1[2] = std::numeric_limits<float>::infinity();
    }

    // Swap t0 and t1 based on the ray direction
    if (direction.x < 0.0f) 
        std::swap(t0[0], t1[0]);
    if (direction.y < 0.0f) 
        std::swap(t0[1], t1[1]);
    if (direction.z < 0.0f) 
        std::swap(t0[2], t1[2]);

    // Calculate the nearest and farthest intersections
    float tNear = std::max(std::max(t0[0], 
        t0[1]), t0[2]);
    float tFar = std::min(std::min(t1[0],
        t1[1]), t1[2]);

    // Check for parallel rays (no intersection)
    if (tNear > tFar || tFar < 0)
    {
        return false; // No intersection
    }

    // Return the intersection distance 
    if (tNear >= 0) 
    {
        t = tNear;
    }
    else 
    {
        t = tFar;
    }
    return true; 
}

Vector3D Ray::getOrigin() const
{
    return this->origin;
}

Vector3D Ray::getDirection() const
{
    return this->direction;
}
