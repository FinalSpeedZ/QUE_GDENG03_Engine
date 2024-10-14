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

	srand(time(0));

	InputSystem::initialize();
	GraphicsEngine::initialize();
	GameObjectManager::initialize();

	m_swap_chain = GraphicsEngine::getInstance()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	GameObjectManager::getInstance()->addPrimitives(PrimitiveType::CUBE, 1);
}

void AppWindow::onUpdate()
{

	Window::onUpdate();

	InputSystem::getInstance()->update();

	if (m_is_run)
	{
		GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
			0.0f, 0.0f, 0.0f, 1);

		RECT rc = this->getClientWindowRect();
		GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

		GameObjectManager::getInstance()->updateAllPrimitives(EngineTime::getDeltaTime());

		m_swap_chain->present(true);
	}

}

void AppWindow::onDestroy()
{
	if (m_swap_chain) 
	{
		m_swap_chain->release(); 
		m_swap_chain = nullptr; 
	}

	GameObjectManager::getInstance()->destroyAllPrimitives();

	if (GraphicsEngine::getInstance()) 
	{
		GraphicsEngine::getInstance()->release();
	}

	Window::onDestroy(); // Call the base class cleanup
}

void AppWindow::onFocus()
{
	Window::onFocus();

	InputSystem::getInstance()->addListener(this);
}

void AppWindow::onKillFocus()
{
	Window::onKillFocus();

	InputSystem::getInstance()->removeListener(this);
}

void AppWindow::onKeyDown(int key)
{
	// Esc
	if (key == 27)
	{
		onDestroy();
	}
}

void AppWindow::onKeyUp(int key)
{
}

void AppWindow::onMouseMove(const Point& delta_mouse_pos)
{
	GameObjectManager::getInstance()->rotatePrimitiveType(PrimitiveType::CUBE,
													(-delta_mouse_pos.y * EngineTime::getDeltaTime()),
													(-delta_mouse_pos.x * EngineTime::getDeltaTime()),
													0);
}

void AppWindow::onLeftMouseDown(const Point& mouse_pos)
{
}

void AppWindow::onLeftMouseUp(const Point& mouse_pos)
{
}

void AppWindow::onRightMouseDown(const Point& mouse_pos)
{
}

void AppWindow::onRightMouseUp(const Point& mouse_pos)
{
}



