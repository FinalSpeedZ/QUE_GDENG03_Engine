#include "AppWindow.h"

#include <corecrt_math_defines.h>

#include "Camera.h"
#include "InputSystem.h"
#include "SceneCameraHandler.h"

#include "Libs/imgui/imgui.h"
#include "Libs/imgui/imgui_impl_dx11.h"
#include "Libs/imgui/imgui_impl_win32.h"
#include "UIManager.h"

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
	TextureManager::initialize();
	InputSystem::initialize();
	GameObjectManager::initialize();
	SceneCameraHandler::initialize();
	UIManager::initialize(this->m_hwnd);

	RECT rc = this->getClientWindowRect();
	m_swap_chain = GraphicsEngine::getInstance()->getRenderSystem()->createSwapChain(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);
	GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	GameObjectManager::getInstance()->createPrimitive(PrimitiveType::CUBE);

	//GameObjectManager::getInstance()->createPrimitive(PrimitiveType::PLANE);
}

void AppWindow::onUpdate()
{
	InputSystem::getInstance()->update();

	if (isRunning())
	{
		GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
			0.5f, 0.5f, 0.8f, 1);

		RECT rc = this->getClientWindowRect();
		GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

		SceneCameraHandler::getInstance()->update();

		GameObjectManager::getInstance()->updateAll(EngineTime::getDeltaTime());

		UIManager::getInstance()->drawAllUI();

		m_swap_chain->present(true);
	}
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
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


