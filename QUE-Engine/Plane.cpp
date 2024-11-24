#include "Plane.h"

#define _USE_MATH_DEFINES
#include "math.h"

Plane::Plane(std::string name, float width, float depth)
	: Drawable(name), width(width), depth(depth)
{
	calculateVertices();
}

void Plane::onCreate()
{
	UINT size_index_list = index_list.size();

	m_ib = GraphicsEngine::getInstance()->getRenderSystem()->createIndexBuffer(index_list, size_index_list);

	Drawable::onCreate();
}

void Plane::onUpdate(float deltaTime)
{
	Drawable::onUpdate(deltaTime);
}

void Plane::onDestroy()
{
	Drawable::onDestroy();
}

void Plane::draw()
{
	Drawable::draw();

	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
}

void Plane::calculateVertices()
{

	vertices.clear();

	float halfWidth = width / 2.0f;
	float halfDepth = depth / 2.0f;

	Vector3D initPositions[4] =
	{
		// Front plane vertices
		Vector3D(-halfWidth, 0.0f, -halfDepth) + localPosition, // Bottom Left Front
		Vector3D(-halfWidth, 0.0f, halfDepth) + localPosition,  // Top Left Front
		Vector3D(halfWidth, 0.0f, -halfDepth) + localPosition,   // Bottom Right Front
		Vector3D(halfWidth, 0.0f, halfDepth) + localPosition,    // Top Right Front
	};

	vertices =
	{
		{ initPositions[0], Colors::RED, Colors::RED }, // Bottom Left Front
		{ initPositions[1], Colors::GREEN, Colors::GREEN }, // Top Left Front
		{ initPositions[2], Colors::YELLOW, Colors::YELLOW }, // Bottom Right Front
		{ initPositions[3], Colors::BLUE, Colors::BLUE }  // Top Right Front
	};

	index_list =
	{
		0, 1, 2,
		1, 3, 2,
		2, 1, 0,
		2, 3, 1
	};

}

void Plane::updateConstantBuffer(float deltaTime)
{
	Drawable::updateConstantBuffer(deltaTime);
}

void Plane::projectionViewMatrix()
{
	Drawable::projectionViewMatrix();
}