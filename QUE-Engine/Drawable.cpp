#include "Drawable.h"

#include <algorithm>
#include <corecrt_math_defines.h>
#include <iostream>

#include "AppWindow.h"
#include "Camera.h"
#include "SceneCameraHandler.h"


Drawable::Drawable(std::string name)
	: GameObject(name)
{
}

void Drawable::onCreate()
{
	calculateVertices();

	cc.m_time = 0.0f;

	m_cb = GraphicsEngine::getInstance()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant));

	UINT size_list = vertices.size();

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::getInstance()->getRenderSystem()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::getInstance()->getRenderSystem()->createVertexShader(shader_byte_code, size_shader);
	m_vb = GraphicsEngine::getInstance()->getRenderSystem()->createVertexBuffer(vertices, sizeof(vertex), size_list, shader_byte_code, size_shader);
	GraphicsEngine::getInstance()->getRenderSystem()->releaseCompiledShader();

	GraphicsEngine::getInstance()->getRenderSystem()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::getInstance()->getRenderSystem()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::getInstance()->getRenderSystem()->releaseCompiledShader();
}

void Drawable::onUpdate(float deltatime)
{
	onCreate();

	GameObject::onUpdate(deltatime);

	projectionViewMatrix();
	updateConstantBuffer(deltatime);
	draw();
}

void Drawable::onDestroy()
{
	GameObject::onDestroy();
}

void Drawable::draw()
{
	m_cb->update(GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext(), &cc);

	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
}

void Drawable::updateConstantBuffer(float deltaTime)
{
	cc.m_time = 0.0f;

	time += animSpeed * deltaTime;
	cc.m_time = time;

	Matrix4x4 temp;

	cc.m_world.setIdentity();

	temp.setIdentity();
	temp.setScale(getLocalScale());
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationX(getLocalRotation().x);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationY(getLocalRotation().y);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationZ(getLocalRotation().z);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setTranslation(localPosition);
	cc.m_world *= temp;
}

void Drawable::projectionViewMatrix()
{
	cc.m_projection = SceneCameraHandler::getInstance()->getActiveCamera()->getProjectionMatrix();
	cc.m_view = SceneCameraHandler::getInstance()->getActiveCamera()->getViewMatrix();
}

float Drawable::getAnimSpeed()
{
	return animSpeed;
}

BoundingBox Drawable::getBoundingBox() const
{
	Vector3D min =
	{
		this->localPosition.x - (this->localScale.x * 0.5f),
		this->localPosition.y - (this->localScale.y * 0.5f),
		this->localPosition.z - (this->localScale.z * 0.5f)
	};

	Vector3D max =
	{
		this->localPosition.x + (this->localScale.x * 0.5f),
		this->localPosition.y + (this->localScale.y * 0.5f),
		this->localPosition.z + (this->localScale.z * 0.5f)
	};

	return BoundingBox(min, max);
}

void Drawable::setSelected(bool selected)
{
	this->selected = selected;
}

bool Drawable::getSelected()
{
	return this->selected;
}

float Drawable::randomFloat(float min, float max)
{
	float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (max - min));

	random = min + random;

	return random;
}

Vector4D Drawable::randomColor()
{
	return Vector4D(randomFloat(0.0f, 1.0f),
		randomFloat(0.0f, 1.0f),
		randomFloat(0.0f, 1.0f),
		1.0f);
}

