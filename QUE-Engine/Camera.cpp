#include "Camera.h"

#include <corecrt_math_defines.h>

#include "AppWindow.h"
#include "InputSystem.h"


Camera::Camera(std::string name)
	: GameObject(name)
{
	localPosition.z = -5.0;
	this->updateViewMatrix();

	InputSystem::getInstance()->addListener(this);
}

Camera::~Camera()
{
	InputSystem::getInstance()->removeListener(this);
}

void Camera::onCreate()
{
	GameObject::onCreate();
}

void Camera::onUpdate(float deltatime)
{
	GameObject::onUpdate(deltatime);

	float moveSpeed = 10.0f;

	float x = localPosition.x;
	float y = localPosition.y;
	float z = localPosition.z;

	Vector3D newPosition = localPosition;

	if (InputSystem::getInstance()->isKeyDown('W'))
	{
		newPosition = newPosition + this->localMatrix.getZDirection() * (moveSpeed * deltatime); 
	}

	if (InputSystem::getInstance()->isKeyDown('S'))
	{
		newPosition = newPosition - this->localMatrix.getZDirection() * (moveSpeed * deltatime); 
	}

	if (InputSystem::getInstance()->isKeyDown('A'))
	{
		newPosition = newPosition - this->localMatrix.getXDirection() * (moveSpeed * deltatime); 
	}

	if (InputSystem::getInstance()->isKeyDown('D'))
	{
		newPosition = newPosition + this->localMatrix.getXDirection() * (moveSpeed * deltatime); 
	}

	if (InputSystem::getInstance()->isKeyDown('Q'))
	{
		newPosition = newPosition + this->localMatrix.getYDirection() * (moveSpeed * deltatime); 
	}

	if (InputSystem::getInstance()->isKeyDown('E'))
	{
		newPosition = newPosition - this->localMatrix.getYDirection() * (moveSpeed * deltatime); 
	}

	if (newPosition != localPosition)
	{
		setPosition(newPosition.x, newPosition.y, newPosition.z);
		this->updateViewMatrix();
	}

}

void Camera::onDestroy()
{
	GameObject::onDestroy();
}

void Camera::updateViewMatrix()
{
	Matrix4x4 worldCam;
	worldCam.setIdentity();

	Matrix4x4 temp;
	temp.setIdentity();

	temp.setIdentity();
	temp.setScale(localScale);
	worldCam *= temp;

	temp.setIdentity();
	temp.setRotationX(localRotation.x);
	worldCam *= temp;

	temp.setIdentity();
	temp.setRotationY(localRotation.y);
	worldCam *= temp;

	temp.setIdentity();
	temp.setRotationZ(localRotation.z);
	worldCam *= temp;

	temp.setTranslation(localPosition);
	worldCam *= temp;

	worldCam.inverse();

	this->localMatrix = worldCam;
}


Matrix4x4 Camera::getViewMatrix()
{
	return this->localMatrix;
}

void Camera::onKeyDown(int key)
{
}

void Camera::onKeyUp(int key)
{
}

void Camera::onMouseMove(const Vector2D& deltaPos)
{

	if (this->mouseDown)
	{
		RECT rc = AppWindow::getInstance()->getClientWindowRect();
		int width = rc.right - rc.left;
		int height = rc.bottom - rc.top;

		float x = localRotation.x;
		float y = localRotation.y;
		float z = localRotation.z;

		x += 0.1f * (deltaPos.y - (height / 2.0f)) * EngineTime::getDeltaTime();
		y += 0.1f * (deltaPos.x - (width / 2.0f)) * EngineTime::getDeltaTime();

		this->setRotation(x, y, z);
		this->updateViewMatrix();

		InputSystem::getInstance()->setCursorPosition(Vector2D(width / 2.0f, height / 2.0));
	}
}

void Camera::onLeftMouseDown(const Vector2D& deltaPos)
{
}

void Camera::onLeftMouseUp(const Vector2D& deltaPos)
{
}

void Camera::onRightMouseDown(const Vector2D& deltaPos)
{
	this->mouseDown = true;
}

void Camera::onRightMouseUp(const Vector2D& deltaPos)
{
	this->mouseDown = false;
}

