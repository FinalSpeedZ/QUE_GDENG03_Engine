#include "BlendState.h"


BlendState::BlendState()
{
	blendDesc = {};
}

BlendState::~BlendState()
{
}

void BlendState::release()
{
	m_bs->Release();
	delete this;
}

void BlendState::apply(float blendFactor[4], UINT sampleMask)
{
	if (!blendFactor)
	{
		blendFactor = new float[4] { 0, 0, 0, 0 };
	}

	GraphicsEngine::get()->getImmediateDeviceContext()->getDeviceContext()->OMSetBlendState(m_bs, blendFactor, sampleMask);
}


bool BlendState::init(const D3D11_BLEND_DESC& desc)
{
	blendDesc = desc;
	if (!SUCCEEDED(GraphicsEngine::get()->m_d3d_device->CreateBlendState(&blendDesc, &m_bs)))
		return false;

	return true;
}
