#pragma once

#include <vector>

#include "GameObject.h"
#include "VertexBuffer.h"

__declspec(align(16))
struct constant
{
	float m_time;
};


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

protected:
	virtual void calculateVertices() {};
	virtual void updateConstantBuffer(float deltaTime);

protected:
	std::vector<vertex> vertices;

	constant cc;

	VertexBuffer* m_vb;
	ConstantBuffer* m_cb;
	VertexShader* m_vs;
	PixelShader* m_ps;

	float time = 0.0f;
	float animSpeed = 1.0f;

};

