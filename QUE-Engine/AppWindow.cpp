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

	GameObjectManager::initialize();

	m_swap_chain = GraphicsEngine::getInstance()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	GameObjectManager::getInstance()->createPrimitive(PrimitiveType::CUBE);
	GameObjectManager::getInstance()->createPrimitive(PrimitiveType::CAMERA);

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

	else if (key == 'W')
	{
		float rotX = GameObjectManager::getInstance()->getLastObject()->getLocalRotation().x;
		rotX += EngineTime::getDeltaTime();
		GameObjectManager::getInstance()->getLastObject()->setRotationX(rotX);
	}

	else if (key == 'S')
	{
		float rotX = GameObjectManager::getInstance()->getLastObject()->getLocalRotation().x;
		rotX -= EngineTime::getDeltaTime();
		GameObjectManager::getInstance()->getLastObject()->setRotationX(rotX);
	}

	else if (key == 'A')
	{
		float rotY = GameObjectManager::getInstance()->getLastObject()->getLocalRotation().y;
		rotY += EngineTime::getDeltaTime();
		GameObjectManager::getInstance()->getLastObject()->setRotationY(rotY);
	}

	else if (key == 'D')
	{
		float rotY = GameObjectManager::getInstance()->getLastObject()->getLocalRotation().y;
		rotY -= EngineTime::getDeltaTime();
		GameObjectManager::getInstance()->getLastObject()->setRotationY(rotY);
	}
}

void AppWindow::onKeyUp(int key)
{

}

void AppWindow::onMouseMove(const Vector2D& deltaMousePos)
{
	float rotX = GameObjectManager::getInstance()->getLastObject()->getLocalRotation().x;
	float rotY = GameObjectManager::getInstance()->getLastObject()->getLocalRotation().y;
	float rotZ = GameObjectManager::getInstance()->getLastObject()->getLocalRotation().z;

	rotX -= deltaMousePos.y * EngineTime::getDeltaTime();
	rotY -= deltaMousePos.x * EngineTime::getDeltaTime();

	GameObjectManager::getInstance()->getLastObject()->setRotation(rotX, rotY, rotZ);

}

void AppWindow::onLeftMouseDown(const Vector2D& mousePos)
{
	float scaleX = GameObjectManager::getInstance()->getLastObject()->getLocalScale().x;

	scaleX = 0.5;

	GameObjectManager::getInstance()->getLastObject()->setScale(scaleX);

	std::cout << "Here";
}

void AppWindow::onLeftMouseUp(const Vector2D& mousePos)
{
	float scaleX = GameObjectManager::getInstance()->getLastObject()->getLocalScale().x;

	scaleX = 1;

	GameObjectManager::getInstance()->getLastObject()->setScale(scaleX);
}

void AppWindow::onRightMouseDown(const Vector2D& mousePos)
{
	float scaleX = GameObjectManager::getInstance()->getLastObject()->getLocalScale().x;

	scaleX = 2;

	GameObjectManager::getInstance()->getLastObject()->setScale(scaleX);
}

void AppWindow::onRightMouseUp(const Vector2D& mousePos)
{
	float scaleX = GameObjectManager::getInstance()->getLastObject()->getLocalScale().x;

	scaleX = 1;

	GameObjectManager::getInstance()->getLastObject()->setScale(scaleX);
}


