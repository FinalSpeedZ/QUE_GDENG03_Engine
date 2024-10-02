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

    vec3 initPositions[4] = 
    {
        vec3(m_origin.x - halfWidth, m_origin.y - halfHeight, m_origin.z),
    	vec3(m_origin.x - halfWidth, m_origin.y + halfHeight, m_origin.z),
        vec3(m_origin.x + halfWidth, m_origin.y - halfHeight, m_origin.z),
    	vec3(m_origin.x + halfWidth, m_origin.y + halfHeight, m_origin.z)
    };

    m_vertices = 
    {
        { initPositions[0], initPositions[0], m_rgba, vec4(m_rgba.x, m_rgba.y, m_rgba.z, 0)}, // Bottom Left
        { initPositions[1], initPositions[1], m_rgba, vec4(m_rgba.x, m_rgba.y, m_rgba.z, 0)}, // Top Left
        { initPositions[2], initPositions[2], m_rgba, vec4(m_rgba.x, m_rgba.y, m_rgba.z, 0)}, // Bottom Right
        { initPositions[3], initPositions[3], m_rgba, vec4(m_rgba.x, m_rgba.y, m_rgba.z, 0)}  // Top Right
    };

}

