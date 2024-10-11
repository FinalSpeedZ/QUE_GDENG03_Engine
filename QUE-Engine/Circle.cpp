#include "Circle.h"

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
	Drawable::deltaTime = deltaTime;

	draw();
}


void Circle::onDestroy()
{
	if (m_vb)
		m_vb->release();

	if (m_vs)
		m_vs->release();

	if (m_ps)
		m_ps->release();
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
	float angleIncrement = 2.0f * 3.14159f / numSegments;

	vertices.push_back({ Vector3D(0.0f, 0.0f, 0.0f), Colors::RED }); 

	for (int i = 0; i <= numSegments; ++i)
	{
		float angle = i * angleIncrement;

		float x = radius * cos(angle);
		float y = radius * sin(angle);

		vertices.push_back({ Vector3D(x, y, 0.0f), Colors::WHITE });

		if (i > 0)
		{
			vertices.push_back({ Vector3D(0.0f, 0.0f, 0.0f), Colors::RED }); 
		}
	}

	vertices.push_back({ Vector3D(radius, 0.0f, 0.0f), Colors::WHITE });
}

