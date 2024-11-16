#pragma once

#include "GameObject.h"

#include "Drawable.h"
#include "InputListener.h"

class Cube : public Drawable
{

public:
	Cube(std::string name = "Cube", float length = 1.0f);
	~Cube() {};

public:
	void onCreate() override;
	void onUpdate(float deltaTime) override;
	void onDestroy() override;

protected:
	void draw() override;
	void calculateVertices() override;

private:
	void updateConstantBuffer(float deltaTime) override;
	void projectionViewMatrix() override;

protected:
	IndexBufferPtr m_ib;
	std::vector<unsigned int> index_list;

	float length;
};

