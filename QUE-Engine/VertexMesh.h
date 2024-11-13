#pragma once
#include "Vector3D.h"
#include "Vector2D.h"

class VertexMesh
{
public:
	VertexMesh();
	VertexMesh(Vector3D position, Vector2D texcoord);
	VertexMesh(const VertexMesh& vertex);

	~VertexMesh() {};

public:
	Vector3D m_position;
	Vector2D m_texcoord;
};