#include "Triangle.h"

#include <iostream>
#include <list>

Triangle::Triangle(std::string name, float base, float height)
	: Drawable(name), base(base), height(height)
{
	calculateVertices();
}

void Triangle::onCreate()
{
	Drawable::onCreate();
}

void Triangle::onUpdate(float deltaTime)
{
	Drawable::deltaTime = deltaTime;

	draw();
}


void Triangle::onDestroy()
{
	if (m_vb)
		m_vb->release();

	if (m_vs)
		m_vs->release();


	if (m_ps)
		m_ps->release();
}

void Triangle::draw()
{
	Drawable::draw();

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleList(m_vb->getSizeVertexList(), 0);
}

void Triangle::setBase(float base)
{
	this->base = base;
	calculateVertices();
}

void Triangle::setHeight(float height)
{
	this->height = height;
	calculateVertices();
}

void Triangle::calculateVertices()
{
	vertices.clear(); 
	vertices.push_back({ Vector3D(-base / 2, -height / 2, 0.0f), YELLOW }); // Bottom left
	vertices.push_back({ Vector3D(0.0f, height / 2, 0.0f), RED });          // Top
	vertices.push_back({ Vector3D(base / 2, -height / 2, 0.0f), BLUE });    // Bottom right   // Bottom right
}
