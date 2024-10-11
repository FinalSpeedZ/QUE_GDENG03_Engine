#include "Circle.h"

#include <iostream>

Circle::Circle(std::string name, float radius)
	: Drawable(name), radius(radius)
{
	localPosition.m_x = getRandomFloat(-0.9, 0.9);
	localPosition.m_y = getRandomFloat(-0.9, 0.9);

	velocityX = getRandomFloat(-1, 1);
	velocityY = getRandomFloat(-1, 1);

	color.x = getRandomFloat(0, 1);
	color.y = getRandomFloat(0, 1);
	color.z = getRandomFloat(0, 1);
	color.w = 1;


	if (localPosition.m_x > 0)
		localPosition.m_x -= radius;
	else if (localPosition.m_x < 0)
		localPosition.m_x += radius;

	if (localPosition.m_y > 0)
		localPosition.m_y -= radius;
	else if (localPosition.m_y < 0)
		localPosition.m_y += radius;

	calculateVertices();
}

void Circle::onCreate()
{
	Drawable::onCreate();
}

void Circle::onUpdate(float deltaTime)
{
	this->localPosition.m_x += this->velocityX * deltaTime;
	this->localPosition.m_y += this->velocityY * deltaTime;

	if (this->localPosition.m_x >= 1 - this->radius)
	{
		this->velocityX = -velocityX; // reverse
		this->localPosition.m_x = 1 - this->radius; // fix pos
		randomColor(); // change color
	}

	if (this->localPosition.m_x <= -1 + this->radius)
	{
		this->velocityX = -velocityX; // reverse
		this->localPosition.m_x = -1 + this->radius; // fix pos
		randomColor(); // change color
	}

	if (this->localPosition.m_y >= 1 - this->radius)
	{
		this->velocityY = -velocityY; // reverse 
		this->localPosition.m_y = 1 - this->radius; // fix pos
		randomColor(); // change color
	}

	if (this->localPosition.m_y <= -1 + this->radius)
	{
		this->velocityY = -velocityY; // reverse
		this->localPosition.m_y = -1 + this->radius; // fix pos
		randomColor(); // change color
	}

	calculateVertices();

	onCreate();

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
		vertices.push_back({ Vector3D(localPosition.m_x + x, localPosition.m_y + y, 0.0f), color, color });
		vertices.push_back({ Vector3D(localPosition.m_x - x, localPosition.m_y + y, 0.0f), color, color });
		vertices.push_back({ Vector3D(localPosition.m_x + x, localPosition.m_y - y, 0.0f), color, color });
		vertices.push_back({ Vector3D(localPosition.m_x - x, localPosition.m_y - y, 0.0f), color, color });
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

float Circle::getRandomFloat(float min, float max)
{
	float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (max - min));

	random = min + random;

	return random;
}

void Circle::randomColor()
{
	color.x = getRandomFloat(0, 1);
	color.y = getRandomFloat(0, 1);
	color.z = getRandomFloat(0, 1);
	color.w = 1;
}
