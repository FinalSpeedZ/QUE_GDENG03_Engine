#include "Circle.h"

#include <iostream>

Circle::Circle(std::string name, float radius)
	: Drawable(name), radius(radius)
{
	calculateVertices();
}

void Circle::onCreate()
{
	Drawable::onCreate();
}

void Circle::onUpdate(float deltaTime)
{
	Drawable::onUpdate(deltaTime);
}


void Circle::onDestroy()
{
	Drawable::onDestroy();
}

void Circle::draw()
{
	Drawable::draw();

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
}

void Circle::setRadius(float radius)
{
	this->radius = radius;

	calculateVertices();

	onCreate();
}

void Circle::calculateVertices()
{
	vertices.clear();

	float angleIncrement = 3.14159f / numSegments;

	for (int i = 0; i <= numSegments; ++i)
	{
		float angle = i * angleIncrement;

		// Calculate x and y using radius for the current angle
		float x = radius * cos(angle);
		float y = radius * sin(angle);

		// Add vertices for the circle
		vertices.push_back({ Vector3D(+ x,  + y, 0.0f), Colors::RED, Colors::WHITE });
		vertices.push_back({ Vector3D(- x,  + y, 0.0f), Colors::RED, Colors::WHITE });
		vertices.push_back({ Vector3D(+ x, - y, 0.0f), Colors::RED, Colors::WHITE });
		vertices.push_back({ Vector3D(- x, - y, 0.0f), Colors::RED, Colors::WHITE });
	}
}

void Circle::updateConstantBuffer(float deltaTime)
{
	Drawable::updateConstantBuffer(deltaTime);
}

void Circle::projectionMat()
{
	Drawable::projectionMat();
}
