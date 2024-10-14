#pragma once

#include "GameObject.h"

#include "Drawable.h"

class Plane : public Drawable
{

public:
	Plane(std::string name, float width = 1.5f, float height = 1.5f);
	~Plane() {};

public:
	void onCreate() override;
	void onUpdate(float deltaTime) override;
	void onDestroy() override;

protected:
	void draw() override;

public:
	void setWidth(float width);
	void setHeight(float height);

private:
	void calculateVertices() override;
	void updateConstantBuffer(float deltaTime) override;
	void projectionMat() override;

private:
	std::vector<vec4> colors;

	float width;
	float height;
	float depth;

	IndexBuffer* m_ib;
	std::vector<unsigned int> index_list;
};

