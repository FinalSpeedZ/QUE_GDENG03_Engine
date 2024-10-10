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
	Drawable::onUpdate(deltaTime);
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

	onCreate();
}

void Triangle::setHeight(float height)
{
	this->height = height;
	calculateVertices();

	onCreate();
}

void Triangle::calculateVertices()
{
	vertices.clear();

	vertices.push_back({ Vector3D(-base / 2, -height / 2, 0.0f), Colors::YELLOW, Colors::ORANGE}); // Bottom left
	vertices.push_back({ Vector3D(0.0f, height / 2, 0.0f), Colors::RED, Colors::WHITE });          // Top
	vertices.push_back({ Vector3D(base / 2, -height / 2, 0.0f), Colors::BLUE, Colors::GREEN });    // Bottom right   // Bottom right
}

void Triangle::updateConstantBuffer(float deltaTime)
{
	Drawable::updateConstantBuffer(deltaTime);
}

void Triangle::projectionMat()
{
	Drawable::projectionMat();
}

