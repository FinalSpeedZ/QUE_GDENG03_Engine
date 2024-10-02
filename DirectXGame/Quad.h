#pragma once

#include <vector>

#include "Drawable.h"

class Quad : public Drawable
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
