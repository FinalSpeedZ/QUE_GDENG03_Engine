#pragma once

#include <string>
#include <exception>

#include "SwapChain.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Texture.h"

#include "Colors.h"

#include "Prerequisites.h"

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context, RenderSystem* system) : m_system(system), m_device_context(device_context) {};
	~DeviceContext();

	void clearRenderTargetColor(const SwapChainPtr& swap_chain, float red, float green, float blue, float alpha);

	void setVertexBuffer(const VertexBufferPtr& vertex_buffer);

	void setIndexBuffer(const IndexBufferPtr& index_buffer);

	void setConstantBuffer(const ConstantBufferPtr& buffer);

	void setRenderConfig(const VertexShaderPtr& vertex_shader, const PixelShaderPtr& pixel_shader);

	void setTexture(const VertexShaderPtr& vertex_shader, const TexturePtr& texture);
	void setTexture(const PixelShaderPtr& vertex_shader, const TexturePtr& texture);

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
