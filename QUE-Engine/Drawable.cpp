#include "Drawable.h"

#include <iostream>

#include "AppWindow.h"
#include "Camera.h"


Drawable::Drawable(std::string name)
	: GameObject(name)
{
}

void Drawable::onCreate()
{
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

	updateConstantBuffer(deltatime);
	draw();
	projectionMat();
}

void Drawable::onDestroy()
{
	GameObject::onDestroy();

	if (m_vb)
		m_vb->release();

	if (m_vs)
		m_vs->release();

	if (m_ps)
		m_ps->release();

	if (m_cb)
		m_cb->release();
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

}

void Drawable::projectionMat()
{
	cc.m_world.setScale(Vector3D(1, 1, 1));

	RECT rc = AppWindow::getInstance()->getClientWindowRect();
	cc.m_view.setIdentity();

	int width = (rc.right - rc.left);
	int height = (rc.bottom - rc.top);

	Vector3D cameraPosition = Camera::getInstance()->getLocalPosition(); 

	cc.m_view = Camera::getInstance()->generateWorldMatrix();

	cc.m_projection = Camera::getInstance()->perspective();

}

float Drawable::randomFloat(float min, float max)
{
	float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (max - min));

	random = min + random;

	return random;
}

vec4 Drawable::randomColor()
{
	return vec4(randomFloat(0.0f, 1.0f),
		randomFloat(0.0f, 1.0f),
		randomFloat(0.0f, 1.0f),
		1.0f);
}

float Drawable::getAnimSpeed()
{
	return animSpeed;
}


