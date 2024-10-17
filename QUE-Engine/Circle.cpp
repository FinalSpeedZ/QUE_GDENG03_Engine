#include "Circle.h"

#define _USE_MATH_DEFINES
#include "math.h"

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
	float angleIncrement = 2.0f * M_PI / numSegments;

	vertices.push_back({ Vector3D(0.0f, 0.0f, 0.0f), Colors::RED }); 

	for (int i = 0; i <= numSegments; ++i)
	{
		float angle = i * angleIncrement;

		float x = radius * cos(angle);
		float y = radius * sin(angle);

		vertices.push_back({ Vector3D(x, y, 0.0f), Colors::WHITE, Colors::RED});

		if (i > 0)
		{
			vertices.push_back({ Vector3D(0.0f, 0.0f, 0.0f), Colors::RED, Colors::WHITE}); 
		}
	}

	vertices.push_back({ Vector3D(radius, 0.0f, 0.0f), Colors::WHITE, Colors::RED});
}

void Circle::updateConstantBuffer(float deltaTime)
{
	Drawable::updateConstantBuffer(deltaTime);
}

void Circle::projectionMat()
{
	Drawable::projectionMat();
}

