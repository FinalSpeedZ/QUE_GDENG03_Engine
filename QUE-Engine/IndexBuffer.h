#pragma once

#include <d3d11.h>
#include <exception>

#include "RenderSystem.h"

#include "Prerequisites.h"

class IndexBuffer
{
public:
	IndexBuffer(std::vector<unsigned int>& index_list, UINT size_list, RenderSystem* system);
	~IndexBuffer();

	UINT getSizeIndexList();

private:
	UINT m_size_list;

private:
	ID3D11Buffer* m_buffer;
	RenderSystem* m_system = nullptr;
private:
	friend class DeviceContext;
};