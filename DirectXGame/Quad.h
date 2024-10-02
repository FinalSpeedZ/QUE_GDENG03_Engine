#pragma once

#include <vector>

#include "Drawables.h"

class Quad : public Drawables
{
private:
    float m_width;
    float m_height;

public:
    Quad(float width, float height, const vec3& origin, const vec4& rgba);
    ~Quad();

private:
    void generateVertices();
};
