#pragma once

#include <string>

#include "SwapChain.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

#include "Colors.h"

#include "Prerequisites.h"

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context, RenderSystem* system) : m_system(system), m_device_context(device_context) {};
	~DeviceContext() {};

	void clearRenderTargetColor(SwapChain* swap_chain, float red, float green, float blue, float alpha);
	bool release();

	void setVertexBuffer(VertexBuffer* vertex_buffer);

	void setIndexBuffer(IndexBuffer* index_buffer);

	void setConstantBuffer(VertexShader* vertex_shader, ConstantBuffer* buffer);
	void setConstantBuffer(PixelShader* pixel_shader, ConstantBuffer* buffer);

	void setVertexShader(VertexShader* vertex_shader);
	void setPixelShader(PixelShader* pixel_shader);

	void drawTriangleList(UINT vertex_count, UINT start_vertex_index);
	void drawTriangleStrip(UINT vertex_count, UINT start_vertex_index);
	void drawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location);

	void setViewportSize(UINT width, UINT height);

private:
	ID3D11DeviceContext* m_device_context;
	RenderSystem* m_system = nullptr;
private:
	friend class ConstantBuffer;
};
