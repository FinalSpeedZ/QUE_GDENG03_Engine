#include "Drawables.h"

#include <iostream>

Drawables::Drawables()
    : m_vb(nullptr),
	  m_position(0.0f, 0.0f, 0.0f),
      m_scale(1.0f, 1.0f, 1.0f),
	  m_origin(0.0f, 0.0f, 0.0f),
      m_rgba(1, 0, 0, 1)
{
}

Drawables::~Drawables()
{
	if (m_vb)
		m_vb->release();
}

void Drawables::setPosition(const vec3& position)
{
	m_position = position;
}

void Drawables::setScale(const vec3& scale)
{
	m_scale = scale;
}

void Drawables::setOrigin(const vec3& origin)
{
	m_origin = origin;
}

void Drawables::load(void* shader_byte_code, UINT size_byte_shader)
{
	if (!m_vb)
	{
		m_vb = GraphicsEngine::get()->createVertexBuffer();
		UINT size_list = m_vertices.size();
		m_vb->load(m_vertices, sizeof(vertex), size_list, shader_byte_code, size_byte_shader);
	}
}

void Drawables::draw()
{
	if (m_vb)
	{
		GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
		GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
	}
}

