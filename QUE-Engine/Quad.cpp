#include "Quad.h"

#include <iostream>
#include <list>

Quad::Quad(std::string name, float width, float height)
	: Drawable(name), width(width), height(height)
{
	calculateVertices();
}

void Quad::onCreate()
{
	Drawable::onCreate();
}

void Quad::onUpdate(float deltaTime)
{
	Drawable::onUpdate(deltaTime);
}


void Quad::onDestroy()
{
	if (m_vb)
		m_vb->release();

	if (m_vs)
		m_vs->release();

	if (m_ps)
		m_ps->release();
}

void Quad::draw()
{
	Drawable::draw();

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
}

void Quad::setWidth(float width)
{
	this->width = width;

	calculateVertices();

	onCreate();
}

void Quad::setHeight(float height)
{
	this->height = height;

	calculateVertices();

	onCreate();
}

void Quad::calculateVertices()
{
	vertices.clear();

	float halfWidth = width / 2.0f;
	float halfHeight = height / 2.0f;

	Vector3D initPositions[4] =
	{
		Vector3D(-halfWidth, - halfHeight, 0.0f),
		Vector3D(-halfWidth, halfHeight, 0.0f),
		Vector3D(halfWidth, -halfHeight, 0.0f),
		Vector3D(halfWidth, halfHeight, 0.0f)
	};

	vertices =
	{
		{ initPositions[0], Colors::RED, Colors::BLUE}, // Bottom Left
		{ initPositions[1], Colors::YELLOW, Colors::GREEN}, // Top Left
		{ initPositions[2], Colors::GREEN, Colors::YELLOW}, // Bottom Right
		{ initPositions[3], Colors::BLUE, Colors::RED}  // Top Right
	};
}

void Quad::updateConstantBuffer(float deltaTime)
{
	Drawable::updateConstantBuffer(deltaTime);
}

void Quad::projectionMat()
{
	Drawable::projectionMat();
}

