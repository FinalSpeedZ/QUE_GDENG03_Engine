#include "Plane.h"

#define _USE_MATH_DEFINES
#include "math.h"

Plane::Plane(std::string name, float width, float height)
	: Drawable(name), width(width), height(height)
{
	calculateVertices();
}

void Plane::onCreate()
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

void Plane::onUpdate(float deltaTime)
{
	Drawable::onUpdate(deltaTime);
}

void Plane::onDestroy()
{
	Drawable::onDestroy();

	if (m_ib)
		m_ib->release();
}

void Plane::draw()
{
	Drawable::draw();

	// Set the index buffer
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	// Draw the plane using the index buffer
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
}

void Plane::setWidth(float width)
{
	this->width = height;

	calculateVertices();

	onCreate();
}

void Plane::setHeight(float height)
{
	this->height = height;

	calculateVertices();

	onCreate();
}

void Plane::calculateVertices()
{
	vertices.clear();

	float halfWidth = width / 2.0f;
	float halfHeight = height / 2.0f;

	Vector3D initPositions[4] =
	{
		// Front plane vertices
		Vector3D(-halfWidth, 0.0f, -halfHeight) + localPosition, // Bottom Left Front
		Vector3D(-halfWidth, 0.0f, halfHeight) + localPosition,  // Top Left Front
		Vector3D(halfWidth, 0.0f, -halfHeight) + localPosition,   // Bottom Right Front
		Vector3D(halfWidth, 0.0f, halfHeight) + localPosition,    // Top Right Front
	};

	vertices =
	{
		{ initPositions[0], Colors::WHITE, Colors::WHITE }, // Bottom Left Front
		{ initPositions[1], Colors::WHITE, Colors::WHITE }, // Top Left Front
		{ initPositions[2], Colors::WHITE, Colors::WHITE }, // Bottom Right Front
		{ initPositions[3], Colors::WHITE, Colors::WHITE }  // Top Right Front
	};

	index_list =
	{
		0, 1, 2,
		1, 3, 2,
		2, 1, 0,
		2, 3, 1
	};
}

void Plane::updateConstantBuffer(float deltaTime)
{
	Drawable::updateConstantBuffer(deltaTime);

	Matrix4x4 temp;

	temp.setIdentity();

	temp.setTranslation(Vector3D(-localPosition.x, -localPosition.y, -localPosition.z));
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationX(90 * M_PI / 180);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setTranslation(localPosition);
	cc.m_world *= temp;
}

void Plane::projectionMat()
{
	Drawable::projectionMat();
}