#pragma once

#include <vector>

#include "GameObject.h"
#include "VertexBuffer.h"

#include "Matrix4x4.h"

__declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_projection;
	float m_time;
};

class GameObjectManager;

class Drawable : public  GameObject
{

public:
	Drawable(std::string name);
	~Drawable() {};

public:
	virtual void onCreate() override;
	virtual void onUpdate(float deltatime) override;
	virtual void onDestroy() override;

public:
	virtual void draw();

protected:
	virtual void calculateVertices() {};
	virtual void updateConstantBuffer(float deltaTime);
	virtual void projectionMat();

protected:
	float randomFloat(float min, float max);
	vec4 randomColor();

public:
	float getAnimSpeed();

protected:
	std::vector<vertex> vertices;

	constant cc;

	VertexBuffer* m_vb;
	ConstantBuffer* m_cb;
	VertexShader* m_vs;
	PixelShader* m_ps;

	float time = 0.0f;
	float animSpeed = 1.f;

};

