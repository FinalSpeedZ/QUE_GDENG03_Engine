#include "DeviceContext.h"

bool DeviceContext::clearRenderTargetColor(SwapChain* swap_chain, vec4 rgba)
{
	FLOAT clear_color[] = { rgba.x, rgba.y, rgba.z, rgba.w };
	m_device_context->ClearRenderTargetView(swap_chain->m_rtv, clear_color);

	return true;
}

bool DeviceContext::clearRenderTargetColor(SwapChain* swap_chain, std::string hexcode)
{
	vec4 rgba = hexToVec3(hexcode);
	FLOAT clear_color[] = { rgba.x, rgba.y, rgba.z, rgba.w };
	m_device_context->ClearRenderTargetView(swap_chain->m_rtv, clear_color);

	return true;
}

bool DeviceContext::release()
{
	m_device_context->Release();
	delete this;
	return true;
}