#pragma once

#include <d3d11.h>

#include "RenderSystem.h"

#include "Prerequisites.h"

class IndexBuffer
{
public:
	IndexBuffer(RenderSystem* system) : m_system(system), m_buffer(0) {};
	~IndexBuffer() {};

	bool load(std::vector<unsigned int>& index_list, UINT size_list);
	UINT getSizeIndexList();
	bool release();

private:
	UINT m_size_list;

private:
	ID3D11Buffer* m_buffer;
	RenderSystem* m_system = nullptr;
private:
	friend class DeviceContext;
};