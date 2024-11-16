#pragma once
#include "Cube.h"

class PhysicsPlane : public Cube
{

public:
	PhysicsPlane(std::string name = "Plane");
	~PhysicsPlane() {};

public:
	void onCreate() override;
	void onUpdate(float deltaTime) override;
	void onDestroy() override;

protected:
	void draw() override;

private:
	void calculateVertices() override;
	void updateConstantBuffer(float deltaTime) override;
	void projectionViewMatrix() override;

};

