#include "PhysicsPlane.h"

PhysicsPlane::PhysicsPlane(std::string name)
	: Cube(name)
{
	calculateVertices();

	this->setPosition(0.0f, -8.0f, 0.0f);
	this->setScale(25, 0.1f, 25);

	this->computeLocalMatrix();

	this->physicsComponent = new PhysicsComponent("PhysicsComponent_" + this->name, this);
	this->physicsComponent->getRigidBody()->setType(BodyType::STATIC);
	this->attachComponent(physicsComponent);
}

void PhysicsPlane::onDestroy()
{
	Cube::onDestroy();

	if (this->physicsComponent)
	{
		this->detachComponent(this->physicsComponent);
		delete this->physicsComponent;
	}
}
