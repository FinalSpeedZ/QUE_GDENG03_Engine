#include "Drawable.h"

#include <algorithm>
#include <corecrt_math_defines.h>
#include <iostream>

#include "AppWindow.h"
#include "Camera.h"
#include "SceneCameraHandler.h"

#include "Mesh.h"


Drawable::Drawable(std::string name)
	: GameObject(name)
{
}

void Drawable::onCreate()
{
	cc.m_time = 0.0f;
	m_cb = GraphicsEngine::getInstance()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant));

	UINT size_list = vertices.size();

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	if (m_tex != NULL)
		GraphicsEngine::getInstance()->getRenderSystem()->compileVertexShader(L"TexturedVertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	else
		GraphicsEngine::getInstance()->getRenderSystem()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::getInstance()->getRenderSystem()->createVertexShader(shader_byte_code, size_shader);

	m_vb = GraphicsEngine::getInstance()->getRenderSystem()->createVertexBuffer(vertices, sizeof(vertex), size_list, shader_byte_code, size_shader);
	GraphicsEngine::getInstance()->getRenderSystem()->releaseCompiledShader();

	if (m_tex != NULL)
		GraphicsEngine::getInstance()->getRenderSystem()->compilePixelShader(L"TexturedPixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	else
		GraphicsEngine::getInstance()->getRenderSystem()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::getInstance()->getRenderSystem()->createPixelShader(shader_byte_code, size_shader);

	GraphicsEngine::getInstance()->getRenderSystem()->releaseCompiledShader();
}

void Drawable::onUpdate(float deltatime)
{
	GameObject::onUpdate(deltatime);

	projectionViewMatrix();
	updateConstantBuffer(deltatime);
	draw();
}

void Drawable::onDestroy()
{
	GameObject::onDestroy();

	this->detachComponent(this->physicsComponent);
	delete this->physicsComponent;
}

void Drawable::draw()
{
	m_cb->update(GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext(), &cc);

	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_cb);

	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setRenderConfig(m_vs, m_ps);

	if (m_mesh != NULL)
	{
		GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(m_mesh->getVertexBuffer());
		GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(m_mesh->getIndexBuffer());
	}

	else
	{
		GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	}

	if (m_tex != NULL)
	{
		GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setTexture(m_ps, m_tex);
	}

	if (m_mesh != NULL)
	{
		GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(m_mesh->getIndexBuffer()->getSizeIndexList(), 0, 0);
	}
}

void Drawable::updateConstantBuffer(float deltaTime)
{
	cc.m_time = 0.0f;

	time += animSpeed * deltaTime;
	cc.m_time = time;

	if (this->overrideMatrix) 
	{
		cc.m_world = this->localMatrix;
	}

	else
	{
		Matrix4x4 matrix;
		Matrix4x4 temp;

		matrix.setIdentity();

		temp.setIdentity();
		temp.setScale(getLocalScale());
		matrix *= temp;

		temp.setIdentity();
		temp.setRotationX(getLocalRotation().x);
		matrix *= temp;

		temp.setIdentity();
		temp.setRotationY(getLocalRotation().y);
		matrix *= temp;

		temp.setIdentity();
		temp.setRotationZ(getLocalRotation().z);
		matrix *= temp;

		temp.setIdentity();
		temp.setTranslation(localPosition);
		matrix *= temp;

		this->localMatrix = matrix;
		this->cc.m_world = matrix;
	}
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

