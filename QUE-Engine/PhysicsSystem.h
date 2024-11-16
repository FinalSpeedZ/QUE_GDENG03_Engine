#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <reactphysics3d/reactphysics3d.h>

using namespace reactphysics3d;
class PhysicsComponent;
class PhysicsSystem
{
public:
	PhysicsSystem();
	~PhysicsSystem();

	void registerComponent(PhysicsComponent* component);
	void unregisterComponent(PhysicsComponent* component);
	void unregisterComponentByName(std::string name);
	PhysicsComponent* findComponentByName(std::string name);
	std::vector<PhysicsComponent*>  getAllComponents();

	void updateAllComponents();
	PhysicsWorld* getPhysicsWorld();
	PhysicsCommon* getPhysicsCommon();

private:
	std::unordered_map<std::string, PhysicsComponent*> componentTable;
	std::vector<PhysicsComponent*> componentList;

	PhysicsCommon* physicsCommon;
	PhysicsWorld* physicsWorld;

};