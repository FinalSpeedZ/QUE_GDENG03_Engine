#include "PhysicsPlane.h"

PhysicsPlane::PhysicsPlane(std::string name)
	: Cube(name)
{
	calculateVertices();

	this->setPosition(0.0f, -8.0f, 0.0f);
	this->setScale(25, 0.1f, 25);

	this->computeLocalMatrix();

	this->physicsComponent = new PhysicsComponent("PhysicsComponent_" + this->name, this);
	this->attachComponent(physicsComponent);
	this->physicsComponent->getRigidBody()->setType(BodyType::STATIC);
}

void PhysicsPlane::onCreate()
{
	Cube::onCreate();
}

void PhysicsPlane::onUpdate(float deltaTime)
{
	Cube::onUpdate(deltaTime);
}

void PhysicsPlane::onDestroy()
{
	Cube::onDestroy();
}

void PhysicsPlane::draw()
{
	Cube::draw();
}

void PhysicsPlane::calculateVertices()
{
	vertices.clear();
	index_list.clear();

	float halfLength = length / 1.0f;


	Vector3D position_list[] =
	{
		{Vector3D(-halfLength, -halfLength, -halfLength)},
		{Vector3D(-halfLength, halfLength, -halfLength)},
		{Vector3D(halfLength, halfLength, -halfLength)},
		{Vector3D(halfLength, -halfLength, -halfLength)},

		{Vector3D(halfLength, -halfLength, halfLength)},
		{Vector3D(halfLength, halfLength, halfLength)},
		{Vector3D(-halfLength, halfLength, halfLength)},
		{Vector3D(-halfLength, -halfLength, halfLength)},
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
		{ position_list[0],  Colors::WHITE, Colors::WHITE, texcoord_list[1] },
		{ position_list[1],  Colors::WHITE, Colors::WHITE, texcoord_list[0] },
		{ position_list[2],  Colors::WHITE, Colors::WHITE, texcoord_list[2] },
		{ position_list[3],  Colors::WHITE, Colors::WHITE, texcoord_list[3] },

		{ position_list[4],  Colors::WHITE, Colors::WHITE, texcoord_list[1] },
		{ position_list[5],  Colors::WHITE, Colors::WHITE, texcoord_list[0] },
		{ position_list[6],  Colors::WHITE, Colors::WHITE, texcoord_list[2] },
		{ position_list[7],  Colors::WHITE, Colors::WHITE, texcoord_list[3] },

		{ position_list[1],  Colors::WHITE, Colors::WHITE, texcoord_list[1] },
		{ position_list[6],  Colors::WHITE, Colors::WHITE, texcoord_list[0] },
		{ position_list[5],  Colors::WHITE, Colors::WHITE, texcoord_list[2] },
		{ position_list[2],  Colors::WHITE, Colors::WHITE, texcoord_list[3] },

		{ position_list[7],  Colors::WHITE, Colors::WHITE, texcoord_list[1] },
		{ position_list[0],  Colors::WHITE, Colors::WHITE, texcoord_list[0] },
		{ position_list[3],  Colors::WHITE, Colors::WHITE, texcoord_list[2] },
		{ position_list[4],  Colors::WHITE, Colors::WHITE, texcoord_list[3] },

		{ position_list[3],  Colors::WHITE, Colors::WHITE, texcoord_list[1] },
		{ position_list[2],  Colors::WHITE, Colors::WHITE, texcoord_list[0] },
		{ position_list[5],  Colors::WHITE, Colors::WHITE, texcoord_list[2] },
		{ position_list[4],  Colors::WHITE, Colors::WHITE, texcoord_list[3] },

		{ position_list[7],  Colors::WHITE, Colors::WHITE, texcoord_list[1] },
		{ position_list[6],  Colors::WHITE, Colors::WHITE, texcoord_list[0] },
		{ position_list[1],  Colors::WHITE, Colors::WHITE, texcoord_list[2] },
		{ position_list[0],  Colors::WHITE, Colors::WHITE, texcoord_list[3] }
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

void PhysicsPlane::updateConstantBuffer(float deltaTime)
{
	Drawable::updateConstantBuffer(deltaTime);
}

void PhysicsPlane::projectionViewMatrix()
{
	Drawable::projectionViewMatrix();
}
