#include "AppWindow.h"

#include <corecrt_math_defines.h>

#include "Camera.h"
#include "InputSystem.h"
#include "SceneCameraHandler.h"

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
	InputSystem::getInstance()->showCursor(false);

	GameObjectManager::initialize();

	SceneCameraHandler::initialize();

	RECT rc = this->getClientWindowRect();
	m_swap_chain = GraphicsEngine::getInstance()->getRenderSystem()->createSwapChain(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	for (int i = 0; i < 10; i++)
	{
		GameObjectManager::getInstance()->createPrimitive(PrimitiveType::CUBE);
	}

	GameObjectManager::getInstance()->createPrimitive(PrimitiveType::PLANE);

}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	InputSystem::getInstance()->update();

	if (isRunning())
	{
		GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
			0.5f, 0.5f, 0.8f, 1);

		RECT rc = this->getClientWindowRect();
		GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

		GameObjectManager::getInstance()->updateAll(EngineTime::getDeltaTime());

		SceneCameraHandler::getInstance()->update();

		m_swap_chain->present(true);
	}
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	GraphicsEngine::getInstance()->release();
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
	int Esc = 27;


	if (key == Esc)
	{
		onDestroy();
	}
}

void AppWindow::onKeyUp(int key)
{

}

void AppWindow::onMouseMove(const Vector2D& mousePos)
{

}

void AppWindow::onLeftMouseDown(const Vector2D& mousePos)
{

}

void AppWindow::onLeftMouseUp(const Vector2D& mousePos)
{

}

void AppWindow::onRightMouseDown(const Vector2D& mousePos)
{

}

void AppWindow::onRightMouseUp(const Vector2D& mousePos)
{

}


