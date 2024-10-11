#pragma once

#include <d3d11.h>

#include "GraphicsEngine.h"

class DeviceContext;

class IndexBuffer
{
public:
	IndexBuffer();
	~IndexBuffer() {};

	bool load(std::vector<unsigned int>& index_list, UINT size_list);
	UINT getSizeIndexList();
	bool release();

private:
	UINT m_size_list;

private:
	ID3D11Buffer* m_buffer;

private:
	friend class DeviceContext;
};