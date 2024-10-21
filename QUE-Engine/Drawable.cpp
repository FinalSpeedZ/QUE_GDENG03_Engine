#include "Drawable.h"

#include <corecrt_math_defines.h>
#include <iostream>

#include "AppWindow.h"
#include "Camera.h"


Drawable::Drawable(std::string name)
	: GameObject(name)
{
}

void Drawable::onCreate()
{
	calculateVertices();

	cc.m_time = 0.0f;

	m_cb = GraphicsEngine::getInstance()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));

	m_vb = GraphicsEngine::getInstance()->createVertexBuffer();
	UINT size_list = vertices.size();

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::getInstance()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::getInstance()->createVertexShader(shader_byte_code, size_shader);
	m_vb->load(vertices, sizeof(vertex), size_list, shader_byte_code, size_shader);
	GraphicsEngine::getInstance()->releaseCompiledShader();

	GraphicsEngine::getInstance()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::getInstance()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::getInstance()->releaseCompiledShader();
}

void Drawable::onUpdate(float deltatime)
{
	GameObject::onUpdate(deltatime);

	projectionMat();
	updateConstantBuffer(deltatime);
	draw();
}

void Drawable::onDestroy()
{
	if (m_vb)
		m_vb->release();

	if (m_vs)
		m_vs->release();

	if (m_ps)
		m_ps->release();

	if (m_cb)
		m_cb->release();

	GameObject::onDestroy();
}

void Drawable::draw()
{
	m_cb->update(GraphicsEngine::getInstance()->getImmediateDeviceContext(), &cc);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
}

void Drawable::updateConstantBuffer(float deltaTime)
{
	cc.m_time = 0.0f;

	time += animSpeed * deltaTime;

	cc.m_time = time;

	Matrix4x4 temp;

	cc.m_world.setIdentity();

	temp.setIdentity();
	temp.setTranslation(Vector3D(-localPosition.x, -localPosition.y, -localPosition.z));
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setScale(getLocalScale());
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationZ(getLocalRotation().z);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationY(getLocalRotation().y);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationX(getLocalRotation().x);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setTranslation(localPosition);
	cc.m_world *= temp;
}

void Drawable::projectionMat()
{
	Camera* cam = dynamic_cast<Camera*>(GameObjectManager::getInstance()->findGameObjectByName("Camera"));
	if (cam)
	{
		cc.m_view = cam->getUpdatedConstantData().m_view;
		cc.m_projection = cam->getUpdatedConstantData().m_projection;
	}
}

float Drawable::getAnimSpeed()
{
	return animSpeed;
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

