#include "Component.h"

Component::Component(std::string name, ComponentType type, GameObject* owner)
	: name(name), type(type), owner(owner)
{
}

Component::~Component()
{
	this->detachOwner();
}

void Component::attachOwner(GameObject* owner)
{
	this->owner = owner;
}

void Component::detachOwner()
{
	this->owner = NULL;
	delete this;
}

GameObject* Component::getOwner()
{
	return owner;
}

ComponentType Component::getType()
{
	return type;
}

std::string Component::getName()
{
	return name;
}

