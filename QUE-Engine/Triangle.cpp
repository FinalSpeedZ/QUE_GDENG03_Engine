#include "Triangle.h"

#include <iostream>
#include <list>

Triangle::Triangle(std::string name, float base, float height)
	: Drawable(name), base(base), height(height)
{
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
	Drawable::onDestroy();
}

void Triangle::draw()
{
	Drawable::draw();

	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->drawTriangleList(m_vb->getSizeVertexList(), 0);
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

	// Ensure you're creating Vector3D objects correctly
	//vertices.push_back({ localPosition + Vector3D(-base / 2, -height / 2, 0.0f), Colors::YELLOW, Colors::ORANGE }); // Bottom left
	//vertices.push_back({ localPosition + Vector3D(0.0f, height / 2, 0.0f), Colors::RED, Colors::WHITE });          // Top
	//vertices.push_back({ localPosition + Vector3D(base / 2, -height / 2, 0.0f), Colors::BLUE, Colors::GREEN });    // Bottom right
}

void Triangle::updateConstantBuffer(float deltaTime)
{
	Drawable::updateConstantBuffer(deltaTime);
}

void Triangle::projectionViewMatrix()
{
	Drawable::projectionViewMatrix();
}

