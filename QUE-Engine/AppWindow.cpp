#include "AppWindow.h"

AppWindow* AppWindow::sharedInstance = NULL;

AppWindow* AppWindow::getInstance()
{
	return sharedInstance;
}

void AppWindow::initialize()
{
	sharedInstance = new AppWindow();
	sharedInstance->init();
}

void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicsEngine::initialize();

	m_swap_chain = GraphicsEngine::getInstance()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	//drawables.push_back(std::make_unique<Triangle>("Triangle " + std::to_string(drawables.size() + 1)));

	drawables.push_back(std::make_unique<Quad>("Quad " + std::to_string(drawables.size() + 1)));

	//drawables.push_back(std::make_unique<Circle>("Circle " + std::to_string(drawables.size() + 1)));

	for (const auto& drawable : drawables)
	{
		drawable->onCreate();
	}

}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0.0f, 0.0f, 0.0f, 1);

	RECT rc = this->getClientWindowRect();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	for (const auto& drawable : drawables)
	{
		drawable->onUpdate(EngineTime::getDeltaTime());
	}

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	m_swap_chain->release();

	GraphicsEngine::getInstance()->release();
}


