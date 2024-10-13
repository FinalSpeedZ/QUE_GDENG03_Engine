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

	InputSystem::getInstance()->initialize();
	InputSystem::getInstance()->addListener(this->getInstance());

	GraphicsEngine::initialize();
	GameObjectManager::initialize();

	m_swap_chain = GraphicsEngine::getInstance()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	GameObjectManager::getInstance()->addPrimitives(PrimitiveType::CUBE, 100);

	std::cout << "Press Space to start animation\n";

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
	// Start animation
	if (key == ' ')
	{
		startAnim = true;
	}
}

bool AppWindow::isStartAnim()
{
	return startAnim;
}


