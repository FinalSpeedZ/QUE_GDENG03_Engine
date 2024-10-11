#pragma once

#include "GameObject.h"

#include "Drawable.h"

class Triangle : public Drawable
{

public:
	Triangle(std::string name, float base = 1.0f, float height = 1.0f);
	~Triangle() {};

public:
	void onCreate() override;
	void onUpdate(float deltaTime) override;
	void onDestroy() override;

protected:
	void draw() override;

public:
	void setBase(float base);
	void setHeight(float height);

private:
	void calculateVertices() override;
	void updateConstantBuffer(float deltaTime) override;

private:
	std::vector<vec4> colors;

	float base;
	float height;
};

