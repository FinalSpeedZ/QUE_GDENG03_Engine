#pragma once

#include "Window.h"
#include "GraphicsEngine.h"

#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

#include "Vertex.h"

class AppWindow : public Window
{
public:
	AppWindow();
	~AppWindow();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
private:
	SwapChain* m_swap_chain;

	VertexBuffer* m_vbRQ; // Vertex Buffer for Rainbow Quad
	VertexBuffer* m_vbRT; // Vertex Buffer for Rainbow Triangle
	VertexBuffer* m_vbGQ; // Vertex Buffer for Green Quad

	// Vertex and Pixel Shaders
	VertexShader* m_vs;
	PixelShader* m_ps;
};

