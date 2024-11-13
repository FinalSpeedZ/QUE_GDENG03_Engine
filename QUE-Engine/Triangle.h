#pragma once

#include "GameObject.h"

#include "Drawable.h"

class Triangle : public Drawable
{

public:
	Triangle(std::string name = "Triangle", float base = 1.0f, float height = 1.0f);
	~Triangle() {};

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

private:
	float base;
	float height;
};

