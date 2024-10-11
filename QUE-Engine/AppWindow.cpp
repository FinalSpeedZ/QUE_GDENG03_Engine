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

	m_swap_chain = GraphicsEngine::getInstance()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	//drawables.push_back(std::make_unique<Triangle>("Triangle " + std::to_string(drawables.size() + 1)));

	drawables.push_back(std::make_unique<Circle>("Circle " + std::to_string(drawables.size() + 1)));

	//drawables.push_back(std::make_unique<Circle>("Circle " + std::to_string(drawables.size() + 1)));

	for (const auto& drawable : drawables)
	{
		drawable->onCreate();
	}
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

		for (const auto& drawable : drawables)
		{
			drawable->onUpdate(EngineTime::getDeltaTime());
		}

		m_swap_chain->present(true);
	}

}

void AppWindow::onDestroy()
{
	if (m_swap_chain) {
		m_swap_chain->release(); 
		m_swap_chain = nullptr; 
	}

	for (const auto& drawable : drawables)
	{
		drawable->onDestroy();
	}

	if (GraphicsEngine::getInstance()) {
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
	// Space
	if (key == ' ') 
	{
		drawables.push_back(std::make_unique<Circle>("Circle " + std::to_string(drawables.size() + 1)));
		drawables.back()->onCreate();
	}

	// Backspace
	else if (key == '\b') 
	{
		if (drawables.size() > 0)
		{
			drawables.back()->onDestroy();
			drawables.pop_back();

		}

	}

	// Esc
	else if (key == 27) 
	{
		onDestroy();
	}

	// Del
	else if (key == 46)
	{
		for (const auto& drawable : drawables)
		{
			drawable->onDestroy();
		}
		drawables.clear();

	}

}


