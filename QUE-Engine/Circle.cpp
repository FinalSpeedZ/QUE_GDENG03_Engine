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
	float angleIncrement = 0.25f * 3.14159f / numSegments;

	vertices.push_back({ Vector3D(0.0f, 0.0f, 0.0f), Colors::RED }); 

	for (int i = 0; i <= numSegments; ++i)
	{
		float angle = i * angleIncrement;

		float x = radius * cos(angle);
		float y = radius * sin(angle);

		vertices.push_back({ Vector3D(x, y, 0.0f), Colors::WHITE, Colors::RED });
		vertices.push_back({ Vector3D(-x, y, 0.0f), Colors::WHITE, Colors::RED });
		vertices.push_back({ Vector3D(x, -y, 0.0f), Colors::WHITE, Colors::RED });
		vertices.push_back({ Vector3D(-x, -y, 0.0f), Colors::WHITE, Colors::RED });

		vertices.push_back({ Vector3D( y,x, 0.0f), Colors::WHITE, Colors::RED });
		vertices.push_back({ Vector3D(-y, x, 0.0f), Colors::WHITE, Colors::RED });
		vertices.push_back({ Vector3D(y, -x, 0.0f), Colors::WHITE, Colors::RED });
		vertices.push_back({ Vector3D(-y, -x, 0.0f), Colors::WHITE, Colors::RED });

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

