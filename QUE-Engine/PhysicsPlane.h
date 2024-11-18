#pragma once
#include "Cube.h"

class PhysicsPlane : public Cube
{

public:
	PhysicsPlane(std::string name = "Physics Plane");
	~PhysicsPlane() {};

public:
	void onDestroy() override;
};

