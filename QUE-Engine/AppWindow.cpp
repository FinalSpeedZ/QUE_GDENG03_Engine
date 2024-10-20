#include "AppWindow.h"

#include <corecrt_math_defines.h>

#include "Camera.h"
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
	InputSystem::getInstance()->showCursor(false);

	GameObjectManager::initialize();

	m_swap_chain = GraphicsEngine::getInstance()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	GameObjectManager::getInstance()->createPrimitive(PrimitiveType::CAMERA);

	GameObjectManager::getInstance()->createPrimitive(PrimitiveType::CUBE);

	GameObjectManager::getInstance()->createPrimitive(PrimitiveType::PLANE);
	GameObjectManager::getInstance()->getLastObject()->setRotationX(60 * M_PI / 180.0f);

}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	InputSystem::getInstance()->update();

	if (isRunning())
	{
		GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
			0.5f, 0.5f, 0.8f, 1);

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
		//float rotX = GameObjectManager::getInstance()->getLastObject()->getLocalRotation().x;
		//rotX += EngineTime::getDeltaTime();
		//GameObjectManager::getInstance()->getLastObject()->setRotationX(rotX);

		Camera* cam = dynamic_cast<Camera*>(GameObjectManager::getInstance()->findGameObjectByName("Camera"));
		if (cam)
		{
			cam->forward = 1.0f;
		}
	}

	else if (key == 'S')
	{
		//float rotX = GameObjectManager::getInstance()->getLastObject()->getLocalRotation().x;
		//rotX -= EngineTime::getDeltaTime();
		//GameObjectManager::getInstance()->getLastObject()->setRotationX(rotX);

		Camera* cam = dynamic_cast<Camera*>(GameObjectManager::getInstance()->findGameObjectByName("Camera"));
		if (cam)
		{
			cam->forward = -1.0f;
		}
	}

	else if (key == 'A')
	{
		//float rotY = GameObjectManager::getInstance()->getLastObject()->getLocalRotation().y;
		//rotY += EngineTime::getDeltaTime();
		//GameObjectManager::getInstance()->getLastObject()->setRotationY(rotY);

		Camera* cam = dynamic_cast<Camera*>(GameObjectManager::getInstance()->findGameObjectByName("Camera"));
		if (cam)
		{
			cam->rightward = -1.0f;
		}
	}

	else if (key == 'D')
	{
		//float rotY = GameObjectManager::getInstance()->getLastObject()->getLocalRotation().y;
		//rotY -= EngineTime::getDeltaTime();
		//GameObjectManager::getInstance()->getLastObject()->setRotationY(rotY);

		Camera* cam = dynamic_cast<Camera*>(GameObjectManager::getInstance()->findGameObjectByName("Camera"));
		if (cam)
		{
			cam->rightward = 1.0f;
		}
	}
}

void AppWindow::onKeyUp(int key)
{
	Camera* cam = dynamic_cast<Camera*>(GameObjectManager::getInstance()->findGameObjectByName("Camera"));
	if (cam)
	{
		cam->forward = 0.0f;
		cam->rightward	 = 0.0f;
	}
}

void AppWindow::onMouseMove(const Vector2D& mousePos)
{
	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	float rotX = GameObjectManager::getInstance()->findGameObjectByName("Camera")->getLocalRotation().x;
	float rotY = GameObjectManager::getInstance()->findGameObjectByName("Camera")->getLocalRotation().y;
	float rotZ = GameObjectManager::getInstance()->findGameObjectByName("Camera")->getLocalRotation().z;

	rotX += 0.1f * (mousePos.y - (height / 2.0f)) * EngineTime::getDeltaTime();
	rotY += 0.1f * (mousePos.x - (width / 2.0f)) * EngineTime::getDeltaTime();

	GameObjectManager::getInstance()->findGameObjectByName("Camera")->setRotation(rotX, rotY, rotZ);

	InputSystem::getInstance()->setCursorPosition(Vector2D(width / 2.0f, height / 2.0));

}

void AppWindow::onLeftMouseDown(const Vector2D& mousePos)
{
	float scaleX = GameObjectManager::getInstance()->getLastObject()->getLocalScale().x;

	scaleX = 0.5;

	//GameObjectManager::getInstance()->getLastObject()->setScale(scaleX);

}

void AppWindow::onLeftMouseUp(const Vector2D& mousePos)
{
	float scaleX = GameObjectManager::getInstance()->getLastObject()->getLocalScale().x;

	scaleX = 1;

	//GameObjectManager::getInstance()->getLastObject()->setScale(scaleX);
}

void AppWindow::onRightMouseDown(const Vector2D& mousePos)
{
	float scaleX = GameObjectManager::getInstance()->getLastObject()->getLocalScale().x;

	scaleX = 2;

	//GameObjectManager::getInstance()->getLastObject()->setScale(scaleX);
}

void AppWindow::onRightMouseUp(const Vector2D& mousePos)
{
	float scaleX = GameObjectManager::getInstance()->getLastObject()->getLocalScale().x;

	scaleX = 1;

	//GameObjectManager::getInstance()->getLastObject()->setScale(scaleX);
}


