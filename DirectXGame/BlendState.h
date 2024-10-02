#pragma once
#include <d3d11.h>

#include "GraphicsEngine.h"

class GraphicsEngine;

class BlendState
{
public:
	BlendState();
	~BlendState();

	void release();
	void apply(float blendFactor[4] = nullptr, UINT sampleMask = 0xffffffff);
	bool init(const D3D11_BLEND_DESC& desc);

private:
	D3D11_BLEND_DESC blendDesc;

	ID3D11BlendState* m_bs;

private:
	friend class GraphicsEngine;
};
