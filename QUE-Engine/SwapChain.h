#pragma once

#include <d3d11.h>

#include "GraphicsEngine.h"

class SwapChain
{

public:
	SwapChain() {};
	~SwapChain() {};

	bool init(HWND hwnd, UINT width, UINT height);
	bool release();

public:
	bool present(bool vsync);

private:
	IDXGISwapChain* m_swap_chain;
	ID3D11RenderTargetView* m_rtv;

	ID3D11DepthStencilView* m_dsv;

private:
	friend class DeviceContext;
};
