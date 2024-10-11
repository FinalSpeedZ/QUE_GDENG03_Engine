#include "Circle.h"

#include <iostream>

#include "AppWindow.h"

Circle::Circle(std::string name, float radius)
	: Drawable(name), radius(radius)
{
	RECT rc = AppWindow::getInstance()->getClientWindowRect();
	float width = (rc.right - rc.left) / 300.0f;  
	float height = (rc.bottom - rc.top) / 300.0f; 

	localPosition.m_x = getRandomFloat(-width / 2 + radius, width / 2 - radius);
	localPosition.m_y = getRandomFloat(-height / 2 + radius, height / 2 - radius);

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
	//this->localPosition.m_x += this->velocityX * deltaTime;
	//this->localPosition.m_y += this->velocityY * deltaTime;

	RECT rc = AppWindow::getInstance()->getClientWindowRect();
	float width = (rc.right - rc.left) / 300.0f;  
	float height = (rc.bottom - rc.top) / 300.0f; 

	// Check bounds for X coordinate
	if (this->localPosition.m_x >= (width / 2) - this->radius)
	{
		this->velocityX = -velocityX; // Reverse velocity
		this->localPosition.m_x = (width / 2) - this->radius; // Fix position
		randomColor(); // Change color
	}

	if (this->localPosition.m_x <= (-width / 2) + this->radius)
	{
		this->velocityX = -velocityX; // Reverse velocity
		this->localPosition.m_x = (-width / 2) + this->radius; // Fix position
		randomColor(); // Change color
	}

	// Check bounds for Y coordinate
	if (this->localPosition.m_y >= (height / 2) - this->radius)
	{
		this->velocityY = -velocityY; // Reverse velocity
		this->localPosition.m_y = (height / 2) - this->radius; // Fix position
		randomColor(); // Change color
	}

	if (this->localPosition.m_y <= (-height / 2) + this->radius)
	{
		this->velocityY = -velocityY; // Reverse velocity
		this->localPosition.m_y = (-height / 2) + this->radius; // Fix position
		randomColor(); // Change color
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
