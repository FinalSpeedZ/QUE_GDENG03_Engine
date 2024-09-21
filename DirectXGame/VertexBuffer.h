#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <vector>

#include "GraphicsEngine.h"

#include "Vertex.h"

class DeviceContext;

class VertexBuffer
{
public:
	VertexBuffer();
	bool load(std::vector<vertex>& list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader);
	UINT getSizeVertexList();
	bool release();
	~VertexBuffer();
private:
	UINT m_size_vertex;
	UINT m_size_list;
private:
	ID3D11Buffer* m_buffer;
	ID3D11InputLayout* m_layout;
private:
	friend class DeviceContext;
};

