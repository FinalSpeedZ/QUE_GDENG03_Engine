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


	/* TEST CASE 7 */
	//for (int i = 0; i < 15; i++)
	//{
	//	GameObjectManager::getInstance()->createPrimitive(PrimitiveType::PLANE);
	//}

	//GameObjectManager::getInstance()->getObjectAtIndex(1)->setRotationX(M_PI / 2.5);

	//GameObjectManager::getInstance()->getObjectAtIndex(2)->setRotationX(-M_PI / 2.5);
	//GameObjectManager::getInstance()->getObjectAtIndex(2)->setPosition(GameObjectManager::getInstance()->getObjectAtIndex(2)->getLocalPosition() + Vector3D(0, 0, 0.6));

	//GameObjectManager::getInstance()->getObjectAtIndex(3)->setRotationX(M_PI / 2.5);
	//GameObjectManager::getInstance()->getObjectAtIndex(3)->setPosition(GameObjectManager::getInstance()->getObjectAtIndex(3)->getLocalPosition() + Vector3D(0, 0, 0.6 * 2));

	//GameObjectManager::getInstance()->getObjectAtIndex(4)->setRotationX(-M_PI / 2.5);
	//GameObjectManager::getInstance()->getObjectAtIndex(4)->setPosition(GameObjectManager::getInstance()->getObjectAtIndex(4)->getLocalPosition() + Vector3D(0, 0, 0.6 * 3));

	//GameObjectManager::getInstance()->getObjectAtIndex(5)->setRotationX(M_PI / 2.5);
	//GameObjectManager::getInstance()->getObjectAtIndex(5)->setPosition(GameObjectManager::getInstance()->getObjectAtIndex(5)->getLocalPosition() + Vector3D(0, 0, 0.6 * 4));

	//GameObjectManager::getInstance()->getObjectAtIndex(6)->setRotationX(-M_PI / 2.5);
	//GameObjectManager::getInstance()->getObjectAtIndex(6)->setPosition(GameObjectManager::getInstance()->getObjectAtIndex(6)->getLocalPosition() + Vector3D(0, 0, -0.6));

	//GameObjectManager::getInstance()->getObjectAtIndex(7)->setRotationX(M_PI / 2.5);
	//GameObjectManager::getInstance()->getObjectAtIndex(7)->setPosition(GameObjectManager::getInstance()->getObjectAtIndex(7)->getLocalPosition() + Vector3D(0, 1.9, 0.6 * 3));

	//GameObjectManager::getInstance()->getObjectAtIndex(8)->setRotationX(-M_PI / 2.5);
	//GameObjectManager::getInstance()->getObjectAtIndex(8)->setPosition(GameObjectManager::getInstance()->getObjectAtIndex(8)->getLocalPosition() + Vector3D(0, 1.9, 0.6 * 2));

	//GameObjectManager::getInstance()->getObjectAtIndex(9)->setRotationX(M_PI / 2.5);
	//GameObjectManager::getInstance()->getObjectAtIndex(9)->setPosition(GameObjectManager::getInstance()->getObjectAtIndex(9)->getLocalPosition() + Vector3D(0, 1.9, 0.6));

	//GameObjectManager::getInstance()->getObjectAtIndex(10)->setRotationX(-M_PI / 2.5);
	//GameObjectManager::getInstance()->getObjectAtIndex(10)->setPosition(GameObjectManager::getInstance()->getObjectAtIndex(10)->getLocalPosition() + Vector3D(0, 1.9, 0));

	//GameObjectManager::getInstance()->getObjectAtIndex(11)->setRotationX(M_PI / 2.5);
	//GameObjectManager::getInstance()->getObjectAtIndex(11)->setPosition(GameObjectManager::getInstance()->getObjectAtIndex(11)->getLocalPosition() + Vector3D(0, 3.8, 0.6 * 2));

	//GameObjectManager::getInstance()->getObjectAtIndex(12)->setRotationX(-M_PI / 2.5);
	//GameObjectManager::getInstance()->getObjectAtIndex(12)->setPosition(GameObjectManager::getInstance()->getObjectAtIndex(12)->getLocalPosition() + Vector3D(0, 3.8, 0.6));

	//GameObjectManager::getInstance()->getObjectAtIndex(13)->setPosition(GameObjectManager::getInstance()->getObjectAtIndex(13)->getLocalPosition() + Vector3D(0, 1, 0));
	//GameObjectManager::getInstance()->getObjectAtIndex(14)->setPosition(GameObjectManager::getInstance()->getObjectAtIndex(14)->getLocalPosition() + Vector3D(0, 1, 0.6 * 3));
	//GameObjectManager::getInstance()->getObjectAtIndex(15)->setPosition(GameObjectManager::getInstance()->getObjectAtIndex(15)->getLocalPosition() + Vector3D(0, 2.8, 0.8));

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

	int Shift = 16;

	if (key == Esc)
	{
		onDestroy();
	}

	if (key == Shift)
	{
		moveCamera = true;
	}

	else if (key == 'W')
	{
		if (!moveCamera)
		{
			Drawable* drawable = dynamic_cast<Drawable*>(GameObjectManager::getInstance()->getLastObject());

			Vector3D pos = drawable->getLocalPosition();
			pos.z += drawable->getAnimSpeed() * EngineTime::getDeltaTime();
			GameObjectManager::getInstance()->getLastObject()->setPosition(pos);
		}

		else if (moveCamera)
		{
			Camera* cam = dynamic_cast<Camera*>(GameObjectManager::getInstance()->findGameObjectByName("Camera"));
			if (cam)
			{
				cam->forward = 1.0f;
			}
		}
	}

	else if (key == 'S')
	{
		if (!moveCamera)
		{
			Drawable* drawable = dynamic_cast<Drawable*>(GameObjectManager::getInstance()->getLastObject());

			Vector3D pos = drawable->getLocalPosition();
			pos.z -= drawable->getAnimSpeed() * EngineTime::getDeltaTime();
			GameObjectManager::getInstance()->getLastObject()->setPosition(pos);
		}

		else if (moveCamera)
		{
			Camera* cam = dynamic_cast<Camera*>(GameObjectManager::getInstance()->findGameObjectByName("Camera"));
			if (cam)
			{
				cam->forward = -1.0f;
			}
		}
	}

	else if (key == 'A')
	{
		if (!moveCamera)
		{
			Drawable* drawable = dynamic_cast<Drawable*>(GameObjectManager::getInstance()->getLastObject());

			Vector3D pos = drawable->getLocalPosition();
			pos.x -= drawable->getAnimSpeed() * EngineTime::getDeltaTime();
			GameObjectManager::getInstance()->getLastObject()->setPosition(pos);
		}

		else if (moveCamera)
		{
			Camera* cam = dynamic_cast<Camera*>(GameObjectManager::getInstance()->findGameObjectByName("Camera"));
			if (cam)
			{
				cam->rightward = -1.0f;
			}
		}
	}

	else if (key == 'D')
	{
		if (!moveCamera)
		{
			Drawable* drawable = dynamic_cast<Drawable*>(GameObjectManager::getInstance()->getLastObject());

			Vector3D pos = drawable->getLocalPosition();
			pos.x += drawable->getAnimSpeed() * EngineTime::getDeltaTime();
			GameObjectManager::getInstance()->getLastObject()->setPosition(pos);
		}

		else if (moveCamera)
		{
			Camera* cam = dynamic_cast<Camera*>(GameObjectManager::getInstance()->findGameObjectByName("Camera"));
			if (cam)
			{
				cam->rightward = 1.0f;
			}
		}
	}

	else if (key == 'Q')
	{
		if (!moveCamera)
		{
			Drawable* drawable = dynamic_cast<Drawable*>(GameObjectManager::getInstance()->getLastObject());

			Vector3D pos = drawable->getLocalPosition();
			pos.y += drawable->getAnimSpeed() * EngineTime::getDeltaTime();
			GameObjectManager::getInstance()->getLastObject()->setPosition(pos);
		}

		else if (moveCamera)
		{
			Camera* cam = dynamic_cast<Camera*>(GameObjectManager::getInstance()->findGameObjectByName("Camera"));
			if (cam)
			{
				cam->upward = 1.0f;
			}
		}
	}

	else if (key == 'E')
	{
		if (!moveCamera)
		{
			Drawable* drawable = dynamic_cast<Drawable*>(GameObjectManager::getInstance()->getLastObject());

			Vector3D pos = drawable->getLocalPosition();
			pos.y -= drawable->getAnimSpeed() * EngineTime::getDeltaTime();
			GameObjectManager::getInstance()->getLastObject()->setPosition(pos);
		}

		else if (moveCamera)
		{
			Camera* cam = dynamic_cast<Camera*>(GameObjectManager::getInstance()->findGameObjectByName("Camera"));
			if (cam)
			{
				cam->upward = -1.0f;
			}
		}
	}

	else if (key == 'I')
	{
		if (!moveCamera)
		{
			Drawable* drawable = dynamic_cast<Drawable*>(GameObjectManager::getInstance()->getLastObject());

			Vector3D rot = drawable->getLocalRotation();
			rot.x += drawable->getAnimSpeed() * EngineTime::getDeltaTime();
			GameObjectManager::getInstance()->getLastObject()->setRotationX(rot.x);


		}
	}

	else if (key == 'K')
	{
		if (!moveCamera)
		{
			Drawable* drawable = dynamic_cast<Drawable*>(GameObjectManager::getInstance()->getLastObject());

			Vector3D rot = drawable->getLocalRotation();
			rot.x -= drawable->getAnimSpeed() * EngineTime::getDeltaTime();
			GameObjectManager::getInstance()->getLastObject()->setRotationX(rot.x);
		}
	}

	else if (key == 'J')
	{
		if (!moveCamera)
		{
			Drawable* drawable = dynamic_cast<Drawable*>(GameObjectManager::getInstance()->getLastObject());

			Vector3D rot = drawable->getLocalRotation();
			rot.y += drawable->getAnimSpeed() * EngineTime::getDeltaTime();
			GameObjectManager::getInstance()->getLastObject()->setRotationY(rot.y);
		}
	}

	else if (key == 'L')
	{
		if (!moveCamera)
		{
			Drawable* drawable = dynamic_cast<Drawable*>(GameObjectManager::getInstance()->getLastObject());

			Vector3D rot = drawable->getLocalRotation();
			rot.y -= drawable->getAnimSpeed() * EngineTime::getDeltaTime();
			GameObjectManager::getInstance()->getLastObject()->setRotationY(rot.y);

		}
	}

	//else if (key == ' ')
	//{
	//	startAnim = true;
	//}

}

void AppWindow::onKeyUp(int key)
{
	Camera* cam = dynamic_cast<Camera*>(GameObjectManager::getInstance()->findGameObjectByName("Camera"));
	if (cam)
	{
		cam->forward = 0.0f;
		cam->rightward = 0.0f;
		cam->upward = 0.0f;
	}

	int Shift = 16;

	if (key == Shift)
	{
		moveCamera = false;
	}
}

void AppWindow::onMouseMove(const Vector2D& mousePos)
{
	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	if (moveCamera)
	{
		float rotX = GameObjectManager::getInstance()->findGameObjectByName("Camera")->getLocalRotation().x;
		float rotY = GameObjectManager::getInstance()->findGameObjectByName("Camera")->getLocalRotation().y;
		float rotZ = GameObjectManager::getInstance()->findGameObjectByName("Camera")->getLocalRotation().z;

		rotX += 0.1f * (mousePos.y - (height / 2.0f)) * EngineTime::getDeltaTime();
		rotY += 0.1f * (mousePos.x - (width / 2.0f)) * EngineTime::getDeltaTime();

		GameObjectManager::getInstance()->findGameObjectByName("Camera")->setRotation(rotX, rotY, rotZ);

		InputSystem::getInstance()->setCursorPosition(Vector2D(width / 2.0f, height / 2.0));
	}

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


