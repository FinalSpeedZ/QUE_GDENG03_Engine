#pragma once

#include "GameObject.h"

#include "Drawable.h"

class Cube : public Drawable
{

public:
	Cube(std::string name = "Cube", float length = 2.0f);
	~Cube() {};

public:
	void onCreate() override;
	void onUpdate(float deltaTime) override;
	void onDestroy() override;

protected:
	void draw() override;

public:
	void setLength(float length);

private:
	void calculateVertices() override;
	void updateConstantBuffer(float deltaTime) override;
	void projectionMat() override;

private:
	IndexBuffer* m_ib;
	std::vector<unsigned int> index_list;

	float length;
};

