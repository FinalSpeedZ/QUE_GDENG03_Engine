#pragma once

#include <d3d11.h>
#include <exception>

#include "RenderSystem.h"

#include "Prerequisites.h"

class SwapChain
{

public:
	SwapChain(HWND hwnd, UINT width, UINT height, RenderSystem* system);
	~SwapChain();

public:
	bool present(bool vsync);

private:
	IDXGISwapChain* m_swap_chain;
	ID3D11RenderTargetView* m_rtv;

	ID3D11DepthStencilView* m_dsv;

	RenderSystem* m_system = nullptr;
private:
	friend class DeviceContext;
};
