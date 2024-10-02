#include "Drawable.h"

#include <iostream>

Drawable::Drawable()
    : m_vb(nullptr),
	  m_position(0.0f, 0.0f, 0.0f),
      m_scale(1.0f, 1.0f, 1.0f),
	  m_origin(0.0f, 0.0f, 0.0f),
      m_rgba(1, 0, 0, 1)
{
}

Drawable::~Drawable()
{
	if (m_vb)
		m_vb->release();
}

void Drawable::setPosition(const vec3& position)
{
	m_position = position;
}

void Drawable::setScale(const vec3& scale)
{
	m_scale = scale;
}

void Drawable::setOrigin(const vec3& origin)
{
	m_origin = origin;
}

void Drawable::setBlendState(BlendState* blendState)
{
	m_blendState = blendState;
}

BlendState* Drawable::getBlendState()
{
	return m_blendState;
}

void Drawable::load(void* shader_byte_code, UINT size_byte_shader)
{
	if (!m_vb)
	{
		m_vb = GraphicsEngine::get()->createVertexBuffer();
		UINT size_list = m_vertices.size();
		m_vb->load(m_vertices, sizeof(vertex), size_list, shader_byte_code, size_byte_shader);
	}
}

void Drawable::draw()
{
	if (m_vb)
	{
		GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
		GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
	}
}

