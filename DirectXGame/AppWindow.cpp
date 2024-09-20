#include "AppWindow.h"

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
	vec3 color;
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

	// Rainbow Quad
	vertex listRQ[] =
	{
		{-0.9f,0.1f,0.0f, 1.0f, 0.0f, 0.0f}, // V1
		{-0.9f,0.8f,0.0f, 0.0f, 1.0f, 0.0f}, // V2
		{ -0.1f,0.1f,0.0f, 0.0f, 0.0f, 1.0f}, // V3
		{-0.1f,0.8f,0.0f, 1.0f, 1.0f, 0.0f} // V4
	};

	// Rainbow Triangle
	vertex listRT[] =
	{
		{0.1f, 0.1f, 0.0f, 1.0f, 0.0f, 0.0f}, // V1
		{0.5f, 0.8f, 0.0f, 0.0f, 1.0f, 0.0f}, // V2
		{0.9f, 0.1f, 0.0f, 0.0f, 0.0f, 1.0f}  // V3
	};

	// Green Quad
	vertex listGQ[] = 
	{
		{-0.4f,-0.8f,0.0f, 0.0f, 1.0f, 0.0f}, // V1
		{-0.4f,-0.1f,0.0f, 0.0f, 1.0f, 0.0f}, // V2
		{ 0.4f,-0.8f,0.0f, 0.0f, 1.0f, 0.0f}, // V3
		{0.4f,-0.1f,0.0f, 0.0f, 1.0f, 0.0f} // V4
	};

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	// Vertex Shader
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	// Vertex Buffer for Rainbow Quad
	m_vbRQ = GraphicsEngine::get()->createVertexBuffer();
	UINT size_listRQ = ARRAYSIZE(listRQ);
	m_vbRQ->load(listRQ, sizeof(vertex), size_listRQ, shader_byte_code, size_shader);

	// Vertex Buffer for Rainbow Triangle
	m_vbRT = GraphicsEngine::get()->createVertexBuffer();
	UINT size_listRT = ARRAYSIZE(listRT);
	m_vbRT->load(listRT, sizeof(vertex), size_listRT, shader_byte_code, size_shader);

	// Vertex Buffer for Green Quad
	m_vbGQ = GraphicsEngine::get()->createVertexBuffer();
	UINT size_listGQ = ARRAYSIZE(listGQ);
	m_vbGQ->load(listGQ, sizeof(vertex), size_listGQ, shader_byte_code, size_shader);
	
	// Pixel Shader
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0.5f, 0.5f, 0.9f, 1.0f);

	// Set Viewport
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	// Set Default Shader 
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	// Draw Rainbow Quad
	if (m_vbRQ) 
	{
		GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vbRQ);
		GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vbRQ->getSizeVertexList(), 0);
	}

	// Draw Rainbow Triangle
	if (m_vbRT)
	{
		GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vbRT);
		GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vbRT->getSizeVertexList(), 0);
	}

	// Draw Green Quad
	if (m_vbGQ)
	{
		GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vbGQ);
		GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vbGQ->getSizeVertexList(), 0);
	}

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	if (m_vbRQ)
		m_vbRQ->release();

	if (m_vbRT)
		m_vbRT->release();

	if (m_vbGQ)
		m_vbGQ->release();

	m_swap_chain->release();
	m_vs->release();
	m_ps->release();
	GraphicsEngine::get()->release();
}