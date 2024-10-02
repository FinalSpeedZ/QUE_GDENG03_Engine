#pragma once

#include "memory"
#include "vector"

#include "Window.h"
#include "GraphicsEngine.h"

#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

#include "BlendState.h"
#include "BlendStateManager.h"


#include "Drawable.h"
#include "Quad.h"

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

	std::vector<std::unique_ptr<Drawable>> drawables; 

	// Vertex and Pixel Shaders
	VertexShader* m_vs;
	PixelShader* m_ps;

	BlendState* m_bs;

	ConstantBuffer* m_cb;
	unsigned long m_old_time = 0;
	float m_delta_time = 0;
	float m_angle = 0;
};

