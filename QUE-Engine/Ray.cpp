#include "Ray.h"

#include <algorithm>
#include <iostream>


Ray::Ray(const Vector3D& origin, const Vector3D& direction)
	: origin(origin)
{
    this->direction = direction.normalize();
}

bool Ray::intersects(const BoundingBox& box) const
{
    const Vector3D& min = box.min;
    const Vector3D& max = box.max;

    // Define inverse direction and check for zero direction
    Vector3D invDir(
        (direction.x != 0) ? (1.0f / direction.x) : 0,
        (direction.y != 0) ? (1.0f / direction.y) : 0,
        (direction.z != 0) ? (1.0f / direction.z) : 0
    );

    float t0[3], t1[3];

    // Calculate t values for box min and max corners
    t0[0] = (direction.x != 0) ? (min.x - origin.x) * invDir.x : -std::numeric_limits<float>::infinity();
    t1[0] = (direction.x != 0) ? (max.x - origin.x) * invDir.x : std::numeric_limits<float>::infinity();

    t0[1] = (direction.y != 0) ? (min.y - origin.y) * invDir.y : -std::numeric_limits<float>::infinity();
    t1[1] = (direction.y != 0) ? (max.y - origin.y) * invDir.y : std::numeric_limits<float>::infinity();

    t0[2] = (direction.z != 0) ? (min.z - origin.z) * invDir.z : -std::numeric_limits<float>::infinity();
    t1[2] = (direction.z != 0) ? (max.z - origin.z) * invDir.z : std::numeric_limits<float>::infinity();

    // Swap t0 and t1 based on the ray direction
    if (direction.x < 0.0f) std::swap(t0[0], t1[0]);
    if (direction.y < 0.0f) std::swap(t0[1], t1[1]);
    if (direction.z < 0.0f) std::swap(t0[2], t1[2]);

    // Calculate the nearest and farthest intersections
    float tNear = std::max(std::max(t0[0], t0[1]), t0[2]);
    float tFar = std::min(std::min(t1[0], t1[1]), t1[2]);

    // Debugging output
   /* std::cout << "Ray Origin: " << origin.x << ", " << origin.y << ", " << origin.z << std::endl;
    std::cout << "Ray Direction: " << direction.x << ", " << direction.y << ", " << direction.z << std::endl;*/
    //std::cout << "Bounding Box Min: " << min.x << ", " << min.y << ", " << min.z << std::endl;
    //std::cout << "Bounding Box Max: " << max.x << ", " << max.y << ", " << max.z << std::endl;
    //std::cout << "t0: [" << t0[0] << ", " << t0[1] << ", " << t0[2] << "]" << std::endl;
    //std::cout << "t1: [" << t1[0] << ", " << t1[1] << ", " << t1[2] << "]" << std::endl;
    //std::cout << "tNear: " << tNear << ", tFar: " << tFar << std::endl;

    // Check for parallel rays
    if (direction.x == 0 && (origin.x < min.x || origin.x > max.x))
    {
		//std::cout << "No intersection." << std::endl;
        return false;
    }
    if (direction.y == 0 && (origin.y < min.y || origin.y > max.y))
    {
        //std::cout << "No intersection." << std::endl;
        return false;
    }
    if (direction.z == 0 && (origin.z < min.z || origin.z > max.z))
    {
        //std::cout << "No intersection." << std::endl;
        return false;
    }

    // Check if tNear is less than or equal to tFar
    if (tNear <= tFar)
    {
        // We also need to check if the intersection is in the forward direction of the ray
        if (tNear >= 0) {
           // std::cout << "Intersection occurs!" << std::endl;
            return true; // Ray intersects the box
        }
    }
    //std::cout << "No intersection." << std::endl;
    return false; // No intersection
}

Vector3D Ray::getOrigin() const
{
    return this->origin;
}

Vector3D Ray::getDirection() const
{
    return this->direction;
}
