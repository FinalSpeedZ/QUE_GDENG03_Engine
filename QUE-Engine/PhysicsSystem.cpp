#include "PhysicsSystem.h"

#include "EngineTime.h"
#include "PhysicsComponent.h"

PhysicsSystem::PhysicsSystem()
{
	this->physicsCommon = new PhysicsCommon();

	PhysicsWorld::WorldSettings settings;
	settings.defaultVelocitySolverNbIterations = 65;
	settings.gravity = Vector3(0, -9.81, 0);
	this->physicsWorld = this->physicsCommon->createPhysicsWorld(settings);

	std::cout << "[PhysicsSystem]: initialized" << std::endl;
}

PhysicsSystem::~PhysicsSystem()
{
}

void PhysicsSystem::registerComponent(PhysicsComponent* component)
{
    this->componentTable[component->getName()] = component;
    this->componentList.push_back(component);
}

void PhysicsSystem::unregisterComponent(PhysicsComponent* component)
{
    if (!component) 
        return;
    this->componentTable.erase(component->getName());
    this->componentList.erase(
        std::remove(this->componentList.begin(), this->componentList.end(), component),
        this->componentList.end()
    );
}

void PhysicsSystem::unregisterComponentByName(std::string name)
{
    auto it = this->componentTable.find(name);
    if (it != this->componentTable.end())
    {
        PhysicsComponent* component = it->second;
        this->componentList.erase(
            std::remove(this->componentList.begin(), this->componentList.end(), component),
            this->componentList.end()
        );
        this->componentTable.erase(it);
    }
}

PhysicsComponent* PhysicsSystem::findComponentByName(std::string name)
{
    auto it = this->componentTable.find(name);
    if (it != this->componentTable.end())
    {
        return it->second;
    }
    return nullptr;
}

std::vector<PhysicsComponent*> PhysicsSystem::getAllComponents()
{
	return this->componentList;
}

void PhysicsSystem::updateAllComponents()
{
    if (EngineTime::getDeltaTime() > 0.0f)
    {
        this->physicsWorld->update(EngineTime::getDeltaTime());

        for (int i = 0; i < this->componentList.size(); i++)
        {
            this->componentList[i]->perform(EngineTime::getDeltaTime());
        }
    }
}

PhysicsWorld* PhysicsSystem::getPhysicsWorld()
{
	return this->physicsWorld;
}

PhysicsCommon* PhysicsSystem::getPhysicsCommon()
{
	return this->physicsCommon;
}
