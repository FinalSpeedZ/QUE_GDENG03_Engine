#include "Drawable.h"

#include <iostream>

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
}

void Drawable::onDestroy()
{
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
}

