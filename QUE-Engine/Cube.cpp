#include "Cube.h"

#include <corecrt_math_defines.h>
#include <iostream>
#include <list>

#include "AppWindow.h"
#include "InputSystem.h"

Cube::Cube(std::string name, float length)
	: Drawable(name), length(length)
{
	this->localPosition.y = 3.0f;

	calculateVertices();
	//this->physicsComponent = new PhysicsComponent("PhysicsComponent_" + this->name, this);
	//this->attachComponent(physicsComponent);
}

void Cube::onCreate()
{
	UINT size_index_list = index_list.size();

	m_ib = GraphicsEngine::getInstance()->getRenderSystem()->createIndexBuffer(index_list, size_index_list);

	Drawable::onCreate();
}

void Cube::onUpdate(float deltaTime)
{
	Drawable::onUpdate(deltaTime);
}


void Cube::onDestroy()
{
	Drawable::onDestroy();
}

void Cube::draw()
{
	Drawable::draw();

	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
}

void Cube::calculateVertices()
{
	vertices.clear();
	index_list.clear();

	float halfLength = length / 2.0f;


	Vector3D position_list[] =
	{
		{Vector3D(-halfLength, -halfLength, -halfLength) + localPosition},
		{Vector3D(-halfLength, halfLength, -halfLength) + localPosition},
		{Vector3D(halfLength, halfLength, -halfLength) + localPosition},
		{Vector3D(halfLength, -halfLength, -halfLength) + localPosition},

		{Vector3D(halfLength, -halfLength, halfLength) + localPosition},
		{Vector3D(halfLength, halfLength, halfLength) + localPosition},
		{Vector3D(-halfLength, halfLength, halfLength) + localPosition},
		{Vector3D(-halfLength, -halfLength, halfLength) + localPosition},
	};

	Vector2D texcoord_list[] =
	{
		{Vector2D(0.0f, 0.0f)},
		{Vector2D(0.0f, 1.0f)},
		{Vector2D(1.0f, 0.0f)},
		{Vector2D(1.0f, 1.0f)}
	};

	vertices =
	{
		{ position_list[0],  Colors::RED, Colors::RED, texcoord_list[1] },
		{ position_list[1],  Colors::GREEN, Colors::GREEN, texcoord_list[0] },
		{ position_list[2],  Colors::YELLOW, Colors::YELLOW, texcoord_list[2] },
		{ position_list[3],  Colors::BLUE, Colors::BLUE, texcoord_list[3] },

		{ position_list[4],  Colors::RED, Colors::RED, texcoord_list[1] },
		{ position_list[5],  Colors::GREEN, Colors::GREEN, texcoord_list[0] },
		{ position_list[6],  Colors::YELLOW, Colors::YELLOW, texcoord_list[2] },
		{ position_list[7],  Colors::BLUE, Colors::BLUE, texcoord_list[3] },

		{ position_list[1],  Colors::RED, Colors::RED, texcoord_list[1] },
		{ position_list[6],  Colors::GREEN, Colors::GREEN, texcoord_list[0] },
		{ position_list[5],  Colors::YELLOW, Colors::YELLOW, texcoord_list[2] },
		{ position_list[2],  Colors::BLUE, Colors::BLUE, texcoord_list[3] },

		{ position_list[7],  Colors::RED, Colors::RED, texcoord_list[1] },
		{ position_list[0],  Colors::GREEN, Colors::GREEN, texcoord_list[0] },
		{ position_list[3],  Colors::YELLOW, Colors::YELLOW, texcoord_list[2] },
		{ position_list[4],  Colors::BLUE, Colors::BLUE, texcoord_list[3] },

		{ position_list[3],  Colors::RED, Colors::RED, texcoord_list[1] },
		{ position_list[2],  Colors::GREEN, Colors::GREEN, texcoord_list[0] },
		{ position_list[5],  Colors::YELLOW, Colors::YELLOW, texcoord_list[2] },
		{ position_list[4],  Colors::BLUE, Colors::BLUE, texcoord_list[3] },

		{ position_list[7],  Colors::RED, Colors::RED, texcoord_list[1] },
		{ position_list[6],  Colors::GREEN, Colors::GREEN, texcoord_list[0] },
		{ position_list[1],  Colors::YELLOW, Colors::YELLOW, texcoord_list[2] },
		{ position_list[0],  Colors::BLUE, Colors::BLUE, texcoord_list[3] }
	};

	index_list =
	{
		//FRONT SIDE
		0,1,2,  
		2,3,0,  
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		8,9,10,
		10,11,8,
		//BOTTOM SIDE
		12,13,14,
		14,15,12,
		//RIGHT SIDE
		16,17,18,
		18,19,16,
		//LEFT SIDE
		20,21,22,
		22,23,20
	};
}

void Cube::updateConstantBuffer(float deltaTime)
{
	Drawable::updateConstantBuffer(deltaTime);
}

void Cube::projectionViewMatrix()
{
	Drawable::projectionViewMatrix();
}



