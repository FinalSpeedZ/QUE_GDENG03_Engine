#pragma once

#include <vector>

#include "BoundingBox.h"
#include "GameObject.h"
#include "VertexBuffer.h"

#include "Matrix4x4.h"


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
	BoundingBox getBoundingBox() const;

protected:
	float randomFloat(float min, float max);
	Vector4D randomColor();

protected:
	std::vector<vertex> vertices;
	std::vector<Vector4D> colors;

	constant cc;

	VertexBufferPtr m_vb;
	ConstantBufferPtr m_cb;
	VertexShaderPtr m_vs;
	PixelShaderPtr m_ps;

	float time = 0.0f;
	float animSpeed = 1.0f;

};

