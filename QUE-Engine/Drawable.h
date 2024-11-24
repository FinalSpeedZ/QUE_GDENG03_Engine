#pragma once

#include <vector>

#include "GameObject.h"
#include "VertexBuffer.h"

#include "Matrix4x4.h"
#include "PhysicsComponent.h"


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
	virtual void projectionViewMatrix();

public:
	float getAnimSpeed();

protected:
	float randomFloat(float min, float max);
	Vector4D randomColor();

protected:
	std::vector<vertex> vertices;

	constant cc;

	VertexBufferPtr m_vb;
	ConstantBufferPtr m_cb;

	TexturePtr m_tex;
	MeshPtr m_mesh;

	float time = 0.0f;
	float animSpeed = 1.0f;

	PhysicsComponent* physicsComponent;

};

