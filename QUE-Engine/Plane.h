#pragma once

#include "GameObject.h"

#include "Drawable.h"

class Plane : public Drawable
{

public:
	Plane(std::string name = "Plane", float width = 10.0f, float depth = 10.0f);
	~Plane() {};

public:
	void onCreate() override;
	void onUpdate(float deltaTime) override;
	void onDestroy() override;

protected:
	void draw() override;

public:
	void setWidth(float width);
	void setDepth(float depth);

private:
	void calculateVertices() override;
	void updateConstantBuffer(float deltaTime) override;
	void projectionViewMatrix() override;

private:
	float width;
	float depth;

	IndexBufferPtr m_ib;
	std::vector<unsigned int> index_list;
};