#include "Cube.h"

#include <corecrt_math_defines.h>
#include <iostream>
#include <list>

#include "AppWindow.h"
#include "InputSystem.h"

Cube::Cube(std::string name, float length)
	: Drawable(name), length(length)
{
	localPosition.x = randomFloat(-3.0f, 3.0f);
	localPosition.y = randomFloat(-3.0f, 3.0f);
	localPosition.z = randomFloat(-3.0f, 3.0f);

	localRotation.x = randomFloat(0, 2 * M_PI);
	localRotation.y = randomFloat(0, 2 * M_PI);
	localRotation.z = randomFloat(0, 2 * M_PI);
}

void Cube::onCreate()
{
	calculateVertices();

	UINT size_list = vertices.size();

	UINT size_index_list = index_list.size();

	m_ib = GraphicsEngine::getInstance()->getRenderSystem()->createIndexBuffer(index_list, size_index_list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::getInstance()->getRenderSystem()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::getInstance()->getRenderSystem()->createVertexShader(shader_byte_code, size_shader);
	m_vb = GraphicsEngine::getInstance()->getRenderSystem()->createVertexBuffer(vertices, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::getInstance()->getRenderSystem()->releaseCompiledShader();

	GraphicsEngine::getInstance()->getRenderSystem()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::getInstance()->getRenderSystem()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::getInstance()->getRenderSystem()->releaseCompiledShader();

	constant cc;
	cc.m_time = 0;

	m_cb = GraphicsEngine::getInstance()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant));
}

void Cube::onUpdate(float deltaTime)
{
	Drawable::onUpdate(deltaTime);
}


void Cube::onDestroy()
{
	Drawable::onDestroy();

}

void Cube::draw()
{
	Drawable::draw();

	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
}

void Cube::setLength(float length)
{
	this->length = length;

	calculateVertices();

	onCreate();
}

void Cube::calculateVertices()
{
	vertices.clear();
	index_list.clear();

	float halfLength = length / 2.0f;

	Vector3D initPositions[8] =
	{
		Vector3D(-halfLength, -halfLength, -halfLength) + localPosition,
		Vector3D(-halfLength, halfLength, -halfLength) + localPosition,
		Vector3D(halfLength, halfLength, -halfLength) + localPosition,
		Vector3D(halfLength, -halfLength, -halfLength) + localPosition,

		Vector3D(halfLength, -halfLength, halfLength) + localPosition,
		Vector3D(halfLength, halfLength, halfLength) + localPosition,
		Vector3D(-halfLength, halfLength, halfLength) + localPosition,
		Vector3D(-halfLength, -halfLength, halfLength) + localPosition,
	};

	vertices =
	{
		{ initPositions[0], Colors::RED, Colors::RED},
		{ initPositions[1], Colors::YELLOW, Colors::YELLOW},
		{ initPositions[2], Colors::GREEN, Colors::GREEN},
		{ initPositions[3], Colors::BLUE, Colors::BLUE},

		{ initPositions[4], Colors::RED, Colors::RED},
		{ initPositions[5], Colors::YELLOW, Colors::YELLOW},
		{ initPositions[6], Colors::GREEN, Colors::GREEN},
		{ initPositions[7], Colors::BLUE, Colors::BLUE},
	};

	index_list =
	{
		//FRONT SIDE
		0,1,2,  
		2,3,0,  
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};
}

void Cube::updateConstantBuffer(float deltaTime)
{

	//if (InputSystem::getInstance()->isKeyDown('W'))
	//{
	//	localRotation.x += 0.2f;
	//	localRotation.y += 0.2f;
	//	localRotation.z += 0.2f;
	//}

	//if (InputSystem::getInstance()->isKeyDown('S'))
	//{
	//	localRotation.x -= 0.2f;
	//	localRotation.y -= 0.2f;
	//	localRotation.z -= 0.2f;
	//}

	//this->setRotationX(fmod(localRotation.x, 2 * M_PI));
	//this->setRotationY(fmod(localRotation.y, 2 * M_PI));
	//this->setRotationZ(fmod(localRotation.z, 2 * M_PI));

	Drawable::updateConstantBuffer(deltaTime);
}

void Cube::projectionViewMatrix()
{
	Drawable::projectionViewMatrix();
}



