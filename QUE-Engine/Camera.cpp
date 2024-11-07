#include "Camera.h"

#include <corecrt_math_defines.h>

#include "AppWindow.h"
#include "InputSystem.h"
#include "SceneCameraHandler.h"

Camera::Camera(std::string name)
	: GameObject(name)
{
	localPosition.z = -5.0;

	this->updateViewMatrix();

	this->projection = SceneCameraHandler::perspectiveProjection();

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

	setPosition(newPosition.x, newPosition.y, newPosition.z);
	this->updateViewMatrix();
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

	worldCam = worldCam.inverse();

	this->localMatrix = worldCam;
}

Ray Camera::screenToWorldRay(const Vector2D& screenPos)
{
	// Get the dimensions of the viewport
	RECT rc = AppWindow::getInstance()->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	POINT clientPos = {static_cast<LONG>(screenPos.x), static_cast<LONG>(screenPos.y)};
	HWND hwnd = AppWindow::getInstance()->getHWND();
	ScreenToClient(hwnd, &clientPos);

	// Convert screen coordinates to normalized device coordinates (NDC)
	float xNDC = (2.0f * clientPos.x) / width - 1.0f; 
	float yNDC = 1.0f - (2.0f * clientPos.y) / height; 

	// Create the clip space position
	Vector4D clipSpacePos(xNDC, yNDC, -1.0f, 1.0f);

	// Get the inverse projection matrix and view matrix
	Matrix4x4 invProj = this->projection.inverse(); // Inverse of projection matrix

	// Transform to view space
	Vector4D viewSpacePos = invProj * clipSpacePos;
	Vector3D zDirection = this->localMatrix.getZDirection();
	zDirection = zDirection.normalize();

	viewSpacePos.z = 1.0f;
	viewSpacePos.w = 0.0f;

	// Transform to world space
	this->localMatrix.setZDirection(zDirection);

	Matrix4x4 invView = this->localMatrix.inverse(); 
	Vector4D worldSpacePos = invView * viewSpacePos;

	// The direction of the ray
	Vector3D rayDirection(worldSpacePos.x, worldSpacePos.y, worldSpacePos.z);
	rayDirection = rayDirection.normalize(); 

	Vector3D finalDirection = (zDirection + rayDirection);
	finalDirection = finalDirection.normalize();

	return Ray(localPosition, finalDirection);
}


void Camera::pickObject(const Vector2D& mousePos)
{
	Ray ray = screenToWorldRay(mousePos);

	for (GameObject* obj : GameObjectManager::getInstance()->getAllObjects())
	{
		Drawable* drawable = dynamic_cast<Drawable*>(obj);
		if (drawable)
		{
			BoundingBox bbox = drawable->getBoundingBox();

			float t = 0.0f;

			if (ray.intersects(bbox, t)) 
			{
				Vector3D intersectionPoint = ray.getOrigin() + ray.getDirection() * t;

				drawable->setPosition(intersectionPoint.x, intersectionPoint.y, drawable->getLocalPosition().z);
	
				break;
			}
		}
	}
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
		this->updateViewMatrix();

		InputSystem::getInstance()->setCursorPosition(Vector2D(width / 2.0f, height / 2.0));
	}

	if (this->mouseDownLeft)
	{
		this->pickObject(deltaPos);
	}
}

void Camera::onLeftMouseDown(const Vector2D& deltaPos)
{
	this->mouseDownLeft = true;
	this->pickObject(deltaPos);
}

void Camera::onLeftMouseUp(const Vector2D& deltaPos)
{
	this->mouseDownLeft = false;
}

void Camera::onRightMouseDown(const Vector2D& deltaPos)
{
	this->mouseDown = true;
}

void Camera::onRightMouseUp(const Vector2D& deltaPos)
{
	this->mouseDown = false;
}

