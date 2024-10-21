#include "Cube.h"

#include <corecrt_math_defines.h>
#include <iostream>
#include <list>

#include "AppWindow.h"

Cube::Cube(std::string name, float length)
	: Drawable(name), length(length)
{
	//animSpeed = 3.0f;
}

void Cube::onCreate()
{
	calculateVertices();

	m_vb = GraphicsEngine::getInstance()->createVertexBuffer();
	UINT size_list = vertices.size();

	m_ib = GraphicsEngine::getInstance()->createIndexBuffer();
	UINT size_index_list = index_list.size();

	m_ib->load(index_list, size_index_list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::getInstance()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::getInstance()->createVertexShader(shader_byte_code, size_shader);
	m_vb->load(vertices, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::getInstance()->releaseCompiledShader();

	GraphicsEngine::getInstance()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::getInstance()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::getInstance()->releaseCompiledShader();

	constant cc;
	cc.m_time = 0;

	m_cb = GraphicsEngine::getInstance()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));
}

void Cube::onUpdate(float deltaTime)
{
	Drawable::onUpdate(deltaTime);
}


void Cube::onDestroy()
{
	Drawable::onDestroy();

	if (m_ib)
		m_ib->release();
}

void Cube::draw()
{
	Drawable::draw();

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
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
	// Continuous Rotation XYZ
	//this->setRotationX(fmod(localRotation.x, 2 * M_PI));
	//this->setRotationY(fmod(localRotation.y, 2 * M_PI));
	//this->setRotationZ(fmod(localRotation.z, 2 * M_PI));


	/* TEST CASE 3 */
	//this->setScale(Vector3D::lerp(Vector3D(1.0f), Vector3D(0.25f), (sin(time * 2.0f) + 1.0f) / 2.0f));

	//this->setPosition(Vector3D::lerp(Vector3D(-3.0f, -3.0f, 0.0f), Vector3D(3.0f, 3.0f, 0.0f), (sin(time) + 1.0f) / 2.0f));

	/* TEST CASE 5 */
	//if (AppWindow::getInstance()->startAnim)
	//{
	//	if (time <= 1)
	//		this->localScale = Vector3D::lerp(Vector3D(1, 1, 1), Vector3D(5, 0.01, 5), time);
	//}

	Drawable::updateConstantBuffer(deltaTime);
}

void Cube::projectionMat()
{
	Drawable::projectionMat();
}

