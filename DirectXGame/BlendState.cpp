#include "BlendState.h"


BlendState::BlendState()
{
	blendDesc = { 0 };

	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.IndependentBlendEnable = false;

	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
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


bool BlendState::init()
{
	if (!SUCCEEDED(GraphicsEngine::get()->m_d3d_device->CreateBlendState(&blendDesc, &m_bs)))
		return false;

	return true;
}
