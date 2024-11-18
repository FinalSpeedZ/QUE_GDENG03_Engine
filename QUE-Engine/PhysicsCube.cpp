#include "PhysicsCube.h"

PhysicsCube::PhysicsCube(std::string name, float length)
	: Cube(name, length)
{

	this->physicsComponent = new PhysicsComponent("PhysicsComponent_" + this->name, this);
	this->attachComponent(physicsComponent);
}

void PhysicsCube::onDestroy()
{
	Cube::onDestroy();

	if (this->physicsComponent)
	{
		this->detachComponent(this->physicsComponent);
		delete this->physicsComponent;
	}
}
