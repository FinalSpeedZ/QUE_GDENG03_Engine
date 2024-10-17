#pragma once

#include <string>

#include "SwapChain.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

#include "Colors.h"

class SwapChain;
class VertexBuffer;
class IndexBuffer;
class ConstantBuffer;
class VertexShader;
class PixelShader;

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context) : m_device_context(device_context) {};
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

private:
	friend class ConstantBuffer;
};
