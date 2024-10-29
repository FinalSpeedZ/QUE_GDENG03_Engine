#pragma once
#include <d3d11.h>

#include "RenderSystem.h"
#include "DeviceContext.h"

#include "Prerequisites.h"

class ConstantBuffer
{

public:
	ConstantBuffer(RenderSystem* system) : m_system(system) {};
	~ConstantBuffer() {};

	bool load(void* buffer, UINT size_buffer);
	void update(DeviceContext* context, void* buffer);
	bool release();

private:
	ID3D11Buffer* m_buffer;
	RenderSystem* m_system;
private:
	friend class DeviceContext;
};

