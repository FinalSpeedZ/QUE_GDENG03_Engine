#include "VertexMesh.h"

VertexMesh::VertexMesh()
	: m_position(), m_texcoord()
{
}

VertexMesh::VertexMesh(Vector3D position, Vector2D texcoord)
	: m_position(position), m_texcoord(texcoord)
{
}

VertexMesh::VertexMesh(const VertexMesh& vertex)
	: m_position(vertex.m_position), m_texcoord(vertex.m_texcoord)
{
}
