#include "Quad.h"

Quad::Quad(float width, float height, const vec3& origin, const vec4& rgba)
	: m_width(width), m_height(height)
{
	m_origin = origin;
    m_rgba = rgba;
    this->generateVertices();
}

Quad::~Quad()
{
	
}

void Quad::generateVertices()
{
	float halfWidth = m_width / 2.0f;
	float halfHeight = m_height / 2.0f;

    m_vertices = 
    {
        { vec3(m_origin.x - halfWidth, m_origin.y - halfHeight, m_origin.z), m_rgba }, // Bottom Left
        { vec3(m_origin.x - halfWidth, m_origin.y + halfHeight, m_origin.z), m_rgba }, // Top Left
        { vec3(m_origin.x + halfWidth, m_origin.y - halfHeight, m_origin.z), m_rgba }, // Bottom Right
        { vec3(m_origin.x + halfWidth, m_origin.y + halfHeight, m_origin.z), m_rgba }  // Top Right
    };

}

