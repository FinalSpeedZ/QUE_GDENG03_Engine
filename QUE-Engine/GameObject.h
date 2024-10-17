#pragma once

#include <iostream>
#include <string>

#include "Vector3D.h"

class GameObject
{

public:
	GameObject(std::string name);
	~GameObject() {};

public:
	std::string getName();
	void setName(std::string name);

	void setPosition(float x, float y, float z);
	void setPosition(Vector3D pos);
	Vector3D getLocalPosition();

	void setRotation(float x, float y, float z);
	void setRotation(Vector3D rot);
	Vector3D getLocalRotation();

	void setScale(float x, float y, float z);
	void setScale(Vector3D scale);
	Vector3D getLocalScale();

public:
	virtual void onCreate() {};
	virtual void onUpdate(float deltatime) {};
	virtual void onDestroy();

protected:
	std::string name;
	Vector3D localPosition;
	Vector3D localRotation;
	Vector3D localScale;
};

