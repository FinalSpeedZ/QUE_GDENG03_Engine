#pragma once
#include <string>

class PhysicsSystem;

class BaseComponentSystem
{
private:
	BaseComponentSystem();
	~BaseComponentSystem();
	BaseComponentSystem(BaseComponentSystem const&) {};
	BaseComponentSystem& operator = (BaseComponentSystem const&) {};

	static BaseComponentSystem* sharedInstance;

public:
	static BaseComponentSystem* getInstance();

public:
	static void initialize();
	static void destroy();

	PhysicsSystem* getPhysicsSystem();

private:
	PhysicsSystem* physicsSystem;
};