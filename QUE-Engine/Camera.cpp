#include "Camera.h"

#include <corecrt_math_defines.h>

#include "AppWindow.h"
#include "InputSystem.h"
#include "SceneCameraHandler.h"

Camera::Camera(std::string name)
	: GameObject(name)
{
	localPosition.z = -30.0;
	localPosition.y = 5.0f;

	this->projection = SceneCameraHandler::perspectiveProjection();

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

	this->updateViewMatrix();

	float moveSpeed = 3.0f;

	float x = localPosition.x;
	float y = localPosition.y;
	float z = localPosition.z;

	Matrix4x4 viewMatrix = this->localMatrix;
	viewMatrix.inverse();

	Vector3D newPosition = this->localPosition;

	if (InputSystem::getInstance()->isKeyDown('W'))
	{
		newPosition = newPosition + viewMatrix.getZDirection() * (moveSpeed * deltatime);
	}

	if (InputSystem::getInstance()->isKeyDown('S'))
	{
		newPosition = newPosition - viewMatrix.getZDirection() * (moveSpeed * deltatime);
	}

	if (InputSystem::getInstance()->isKeyDown('A'))
	{
		newPosition = newPosition - viewMatrix.getXDirection() * (moveSpeed * deltatime);
	}

	if (InputSystem::getInstance()->isKeyDown('D'))
	{
		newPosition = newPosition + viewMatrix.getXDirection() * (moveSpeed * deltatime);
	}

	if (InputSystem::getInstance()->isKeyDown('Q'))
	{
		newPosition = newPosition + viewMatrix.getYDirection() * (moveSpeed * deltatime);
	}

	if (InputSystem::getInstance()->isKeyDown('E'))
	{
		newPosition = newPosition - viewMatrix.getYDirection() * (moveSpeed * deltatime);
	}

	setPosition(newPosition.x, newPosition.y, newPosition.z);

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

	temp.setRotationX(localRotation.x);
	worldCam *= temp;

	temp.setIdentity();
	temp.setRotationY(localRotation.y);
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

Matrix4x4 Camera::getProjectionMatrix()
{
	return this->projection;
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

