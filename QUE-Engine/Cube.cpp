#include "Cube.h"

#include <iostream>
#include <list>

Cube::Cube(std::string name, float length)
	: Drawable(name), length(length)
{
	calculateVertices();
}

void Cube::onCreate()
{
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

	float halfLength = length / 2.0f;

	Vector3D initPositions[8] =
	{
		Vector3D(-halfLength, -halfLength, -0.5f),
		Vector3D(-halfLength, halfLength, -0.5f),
		Vector3D(halfLength, halfLength, -0.5f),
		Vector3D(halfLength, -halfLength, -0.5f),

		Vector3D(halfLength, -halfLength, 0.5f),
		Vector3D(halfLength, halfLength, 0.5f),
		Vector3D(-halfLength, halfLength, 0.5f),
		Vector3D(-halfLength, -halfLength, 0.5f),
	};

	vertices =
	{
		{ initPositions[0], Colors::RED, Colors::BLUE}, 
		{ initPositions[1], Colors::YELLOW, Colors::GREEN},
		{ initPositions[2], Colors::GREEN, Colors::YELLOW},
		{ initPositions[3], Colors::BLUE, Colors::RED},

		{ initPositions[4], Colors::RED, Colors::BLUE},
		{ initPositions[5], Colors::YELLOW, Colors::GREEN},
		{ initPositions[6], Colors::GREEN, Colors::YELLOW},
		{ initPositions[7], Colors::BLUE, Colors::RED},
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
	Drawable::updateConstantBuffer(deltaTime);

	Matrix4x4 temp;

	cc.m_world.setScale(Vector3D(1));

	temp.setIdentity();
	temp.setRotationZ(getLocalRotation().z);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationY(getLocalRotation().y);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationX(getLocalRotation().x);
	cc.m_world *= temp;
}

void Cube::projectionMat()
{
	Drawable::projectionMat();
}

