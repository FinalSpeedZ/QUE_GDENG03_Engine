#pragma once

#include "GameObject.h"

#include <vector>

class Quad : public GameObject
{
private:
    float m_width;
    float m_height;

public:
    Quad(float width, float height, const vec3& origin, const vec3& fillColor);
    ~Quad();

private:
    void generateVertices();
};