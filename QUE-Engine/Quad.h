#pragma once

#include "GameObject.h"

#include "Drawable.h"

class Quad : public Drawable
{

public:
	Quad(std::string name, float width = 1.0f, float height = 1.0f);
	~Quad() {};

public:
	void onCreate() override;
	void onUpdate(float deltaTime) override;
	void onDestroy() override;

protected:
	void draw() override;

public:
	void setWidth(float width);
	void setHeight(float height);

	void calculateVertices() override;

private:
	std::vector<vec4> colors;

	float width;
	float height;
};

