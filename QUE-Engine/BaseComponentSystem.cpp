#include "BaseComponentSystem.h"

#include "PhysicsSystem.h"

BaseComponentSystem* BaseComponentSystem::sharedInstance = NULL;

BaseComponentSystem::BaseComponentSystem()
{
	this->physicsSystem = new PhysicsSystem();
}

BaseComponentSystem::~BaseComponentSystem()
{
	delete this->physicsSystem;
}

BaseComponentSystem* BaseComponentSystem::getInstance()
{
	return sharedInstance;
}

void BaseComponentSystem::initialize()
{
	sharedInstance = new BaseComponentSystem();

}

void BaseComponentSystem::destroy()
{
	delete sharedInstance;
}

PhysicsSystem* BaseComponentSystem::getPhysicsSystem()
{
	return physicsSystem;
}
