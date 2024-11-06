#pragma once

#include "Vector3D.h"   
#include "BoundingBox.h" 

class Ray {
public:
    Ray(const Vector3D& origin, const Vector3D& direction);

    bool intersects(const BoundingBox& box, float& t) const;

    Vector3D getOrigin() const;
    Vector3D getDirection() const;

private:
    Vector3D origin;
    Vector3D direction;
};
