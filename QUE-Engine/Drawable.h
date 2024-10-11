#pragma once

#include <vector>

#include "GameObject.h"
#include "VertexBuffer.h"

class Drawable : public  GameObject
{

public:
	Drawable(std::string name);
	~Drawable() {};

public:
	virtual void onCreate() override;
	virtual void onUpdate(float deltatime) override;
	virtual void onDestroy() override;

protected:
	virtual void draw();

private:
	virtual void calculateVertices() {};

protected:
	std::vector<vertex> vertices;

	VertexBuffer* m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;

	float deltaTime = 0.0f;
	float animSpeed = 10.0f;

};

