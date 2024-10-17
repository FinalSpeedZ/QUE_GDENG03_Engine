#include "AppWindow.h"

#include "InputSystem.h"

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

	InputSystem::initialize();
	InputSystem::getInstance()->addListener(this);

	GameObjectManager::initialize();

	m_swap_chain = GraphicsEngine::getInstance()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	GameObjectManager::getInstance()->createPrimitive(PrimitiveType::CUBE);

}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	InputSystem::getInstance()->update();

	if (isRunning())
	{
		GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
			0.0f, 0.0f, 0.0f, 1);

		RECT rc = this->getClientWindowRect();
		GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

		GameObjectManager::getInstance()->updateAll(EngineTime::getDeltaTime());

		m_swap_chain->present(true);
	}
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	m_swap_chain->release();

	GraphicsEngine::getInstance()->release();
}

void AppWindow::onFocus()
{
	Window::onFocus();
}

void AppWindow::onKillFocus()
{
	Window::onKillFocus();
}

void AppWindow::onKeyDown(int key)
{
	int Esc = 27;

	if (key == Esc)
	{
		onDestroy();
	}

}

void AppWindow::onKeyUp(int key)
{

}


