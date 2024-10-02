#include "AppWindow.h"

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

	drawables.push_back(std::make_unique<Quad>(0.7f, 0.5f, vec3(0, 0, 0), vec4(1, 0, 0, 0.5)));
	drawables.push_back(std::make_unique<Quad>(0.7f, 0.5f, vec3(-0.5, -0.6, 0), vec4(1, 0, 0, 0.1)));
	drawables.push_back(std::make_unique<Quad>(0.7f, 0.5f, vec3(0.5, 0.6, 0), vec4(1, 0, 0, 1)));

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


	D3D11_BLEND_DESC transparentDesc = { 0 };
	ZeroMemory(&transparentDesc, sizeof(transparentDesc));

	transparentDesc.AlphaToCoverageEnable = false;
	transparentDesc.IndependentBlendEnable = false;

	transparentDesc.RenderTarget[0].BlendEnable = true;
	transparentDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	transparentDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	transparentDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	transparentDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	transparentDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	transparentDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	transparentDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	HRESULT hr = GraphicsEngine::get()->getDevice()->CreateBlendState(&transparentDesc, &TransparentBS);
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0.5f, 0.5f, 0.9f, 1.0f);

	// Set Viewport
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	float blendFactors[] = { 0, 0, 0, 0 };
	GraphicsEngine::get()->getImmediateDeviceContext()->getDeviceContext()->OMSetBlendState(TransparentBS, blendFactors, 0xffffffff);

	// Set Default Shader 
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);


	// Draw Quad
	for (const auto& drawable : drawables)
	{
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