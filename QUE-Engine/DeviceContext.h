#pragma once

#include <string>

#include "SwapChain.h"

#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

#include "Vec.h"
#include "Colors.h"

class SwapChain;
class VertexBuffer;

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context) : m_device_context(device_context) {};
	~DeviceContext() {};

	void clearRenderTargetColor(SwapChain* swap_chain, float red, float green, float blue, float alpha);
	bool release();

	void setVertexBuffer(VertexBuffer* vertex_buffer);
	void setVertexShader(VertexShader* vertex_shader);
	void setPixelShader(PixelShader* pixel_shader);

	void drawTriangleList(UINT vertex_count, UINT start_vertex_index);
	void drawTriangleStrip(UINT vertex_count, UINT start_vertex_index);

	void setViewportSize(UINT width, UINT height);

private:
	ID3D11DeviceContext* m_device_context;
};
