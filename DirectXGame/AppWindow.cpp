#include "AppWindow.h"

__declspec(align(16))
struct constant
{
	float m_angle;
};

AppWindow::AppWindow()
{
}


AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	// Blend State
	BlendStateManager* blendStateManager = new BlendStateManager();
	blendStateManager->initBlendStates();

	drawables.push_back(std::make_unique<Quad>(0.5f, 0.5f, vec3(0, 0.3, 0), vec4(1, 0.5, 0.5, 1)));
	drawables.back()->setBlendState(blendStateManager->getBlendState("AlphaBlend")); 

	drawables.push_back(std::make_unique<Quad>(0.5f, 0.5f, vec3(-0.6, 0.3, 0), vec4(1, 0.5, 0.5, 1))); 
	drawables.back()->setBlendState(blendStateManager->getBlendState("NoBlend"));

	drawables.push_back(std::make_unique<Quad>(0.5f, 0.5f, vec3(0.6, 0.3, 0), vec4(1, 0.5, 0.5, 1)));
	drawables.back()->setBlendState(blendStateManager->getBlendState("CustomBlend1"));

	drawables.push_back(std::make_unique<Quad>(0.5f, 0.5f, vec3(0, -0.3, 0), vec4(1, 0.5, 0.5, 1)));
	drawables.back()->setBlendState(blendStateManager->getBlendState("CustomBlend2"));

	drawables.push_back(std::make_unique<Quad>(0.5f, 0.5f, vec3(-0.6, -0.3, 0), vec4(1, 0.5, 0.5, 1)));
	drawables.back()->setBlendState(blendStateManager->getBlendState("CustomBlend3"));

	drawables.push_back(std::make_unique<Quad>(0.5f, 0.5f, vec3(0.6, -0.3, 0), vec4(1, 0.5, 0.5, 1)));
	drawables.back()->setBlendState(blendStateManager->getBlendState("CustomBlend4"));

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	// Vertex Shader
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	// Vertex Buffer
	for (const auto& gameObject : drawables)
	{
		gameObject->load(shader_byte_code, size_shader);
	}
	
	// Pixel Shader
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

	// Constant Buffer
	constant cc;
	cc.m_angle = 0;
	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0.5f, 0.5f, 0.9f, 1.0f);

	// Set Viewport
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	// Constant Buffer
	unsigned long new_time = 0;
	if (m_old_time)
		new_time = ::GetTickCount() - m_old_time;
	m_delta_time = new_time / 1500.0f;
	m_old_time = ::GetTickCount();

	m_angle += 1.57f * m_delta_time;
	constant cc;
	cc.m_angle = m_angle;

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);

	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);


	// Set Default Shader 
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	// Draw Quad
	for (const auto& drawable : drawables)
	{
		if (drawable->getBlendState() != nullptr)
		{
			GraphicsEngine::get()->applyBlendState(drawable->getBlendState());
		}

		// Draw the drawable
		drawable->draw();
	}

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	m_swap_chain->release();
	m_vs->release();
	m_ps->release();
	GraphicsEngine::get()->release();
}