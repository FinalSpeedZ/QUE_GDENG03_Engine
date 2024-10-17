#pragma once

#include "GameObject.h"

#include "Drawable.h"

class Plane : public Drawable
{

public:
	Plane(std::string name = "Plane", float width = 1.5f, float height = 1.5f);
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
	float width;
	float height;

	IndexBuffer* m_ib;
	std::vector<unsigned int> index_list;
};