#pragma once
#include <d3d11.h>
#include <exception>

#include "RenderSystem.h"
#include "DeviceContext.h"

#include "Prerequisites.h"

class ConstantBuffer
{

public:
	ConstantBuffer(void* buffer, UINT size_buffer, RenderSystem* system);
	~ConstantBuffer();

	void update(DeviceContextPtr context, void* buffer);

private:
	ID3D11Buffer* m_buffer;
	RenderSystem* m_system;
private:
	friend class DeviceContext;
};

