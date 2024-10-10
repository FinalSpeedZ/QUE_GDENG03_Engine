#pragma once

#include <string>

#include "SwapChain.h"

#include "Vec.h"
#include "Colors.h"

class SwapChain;

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context) : m_device_context(device_context) {};
	~DeviceContext() {};


	bool clearRenderTargetColor(SwapChain* swap_chain, vec4 rgba);
	bool clearRenderTargetColor(SwapChain* swap_chain, std::string hexcode);
	bool release();

private:
	ID3D11DeviceContext* m_device_context;
};
