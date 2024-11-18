#pragma once

#include "GameObject.h"

#include "Cube.h"
#include "Drawable.h"
#include "InputListener.h"

class PhysicsCube : public Cube
{

public:
	PhysicsCube(std::string name = "Physics Cube", float length = 1.0f);
	~PhysicsCube() {};

public:
	void onDestroy() override;

};

