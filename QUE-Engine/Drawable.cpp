#include "Drawable.h"

#include <algorithm>
#include <corecrt_math_defines.h>
#include <iostream>

#include "AppWindow.h"
#include "Camera.h"
#include "SceneCameraHandler.h"

#include "Mesh.h"
#include "ShaderLibrary.h"


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


	ShaderNames shaderNames;

	ShaderLibrary::getInstance()->requestVertexShaderData(shaderNames.BASE_VERTEX_SHADER_NAME, &shader_byte_code, &size_shader);
	m_vb = GraphicsEngine::getInstance()->getRenderSystem()->createVertexBuffer(vertices, sizeof(vertex), size_list, shader_byte_code, size_shader);

	ShaderLibrary::getInstance()->requestPixelShaderData(shaderNames.BASE_PIXEL_SHADER_NAME, &shader_byte_code, &size_shader);
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
}

void Drawable::draw()
{
	m_cb->update(GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext(), &cc);

	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_cb);

	ShaderNames shaderNames;
	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setRenderConfig(
		ShaderLibrary::getInstance()->getVertexShader(shaderNames.BASE_VERTEX_SHADER_NAME),
		ShaderLibrary::getInstance()->getPixelShader(shaderNames.BASE_PIXEL_SHADER_NAME));

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
		GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setTexture(
			ShaderLibrary::getInstance()->getPixelShader(shaderNames.TEXTURED_PIXEL_SHADER_NAME),
			m_tex);
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
		this->computeLocalMatrix();
		cc.m_world = this->localMatrix;
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

