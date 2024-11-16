#pragma once
#include <string>

class GameObject;

enum ComponentType
{
	NotSet = -1,
	Script = 0,
	Renderer = 1,
	Input = 2,
	Physics = 3
};

class Component
{
public:

	Component(std::string name, ComponentType type, GameObject* owner);
	~Component();

	void attachOwner(GameObject* owner);
	void detachOwner();
	GameObject* getOwner();
	ComponentType getType();
	std::string getName();

	virtual void perform(float deltaTime) = 0; 

protected:
	GameObject* owner;
	ComponentType type;
	std::string name;
};