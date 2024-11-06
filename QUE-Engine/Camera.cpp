#include "Camera.h"

#include <corecrt_math_defines.h>

#include "AppWindow.h"
#include "InputSystem.h"
#include "SceneCameraHandler.h"

#include <DirectXMath.h>

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

	worldCam = worldCam.inverse();

	this->localMatrix = worldCam;
}

Ray Camera::screenToWorldRay(const Vector2D& screenPos)
{
	RECT rc = AppWindow::getInstance()->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	POINT clientPos = { static_cast<LONG>(screenPos.x), static_cast<LONG>(screenPos.y) };
	HWND hwnd = AppWindow::getInstance()->getHWND();
	ScreenToClient(hwnd, &clientPos);

	float xNDC = (2.0f * clientPos.x / width) - 1.0f; 
	float yNDC = 1.0f - (2.0f * clientPos.y / height); 

	DirectX::XMVECTOR clipSpacePos = DirectX::XMVectorSet(xNDC, yNDC, -1.0f, 1.0f);  

	DirectX::XMMATRIX invProj = DirectX::XMMatrixInverse(nullptr,
		DirectX::XMMatrixSet(
			projection.mat[0][0], projection.mat[0][1], projection.mat[0][2], projection.mat[0][3], 
			projection.mat[1][0], projection.mat[1][1], projection.mat[1][2], projection.mat[1][3],  
			projection.mat[2][0], projection.mat[2][1], projection.mat[2][2], projection.mat[2][3],  
			projection.mat[3][0], projection.mat[3][1], projection.mat[3][2], projection.mat[3][3]   
		));

	DirectX::XMVECTOR viewSpacePos = DirectX::XMVector3TransformCoord(clipSpacePos, invProj);

	DirectX::XMMATRIX viewMatrix = DirectX::XMMatrixSet(
		localMatrix.mat[0][0], localMatrix.mat[0][1], localMatrix.mat[0][2], localMatrix.mat[0][3],  
		localMatrix.mat[1][0], localMatrix.mat[1][1], localMatrix.mat[1][2], localMatrix.mat[1][3],  
		localMatrix.mat[2][0], localMatrix.mat[2][1], localMatrix.mat[2][2], localMatrix.mat[2][3],  
		localMatrix.mat[3][0], localMatrix.mat[3][1], localMatrix.mat[3][2], localMatrix.mat[3][3]   
	);

	DirectX::XMVECTOR zDirection = DirectX::XMVectorSet(localMatrix.getZDirection().x,
			localMatrix.getZDirection().y,
			localMatrix.getZDirection().z, 0.0f);
	zDirection = DirectX::XMVector3Normalize(zDirection);

	DirectX::XMMATRIX invView = DirectX::XMMatrixInverse(nullptr, viewMatrix);  
	DirectX::XMVECTOR worldSpacePos = DirectX::XMVector3TransformCoord(viewSpacePos, invView);

	DirectX::XMVECTOR cameraPosition = DirectX::XMVectorSet(localPosition.x, localPosition.y, localPosition.z, 1.0f);

	DirectX::XMVECTOR rayDirection = DirectX::XMVectorSubtract(worldSpacePos, cameraPosition);
	rayDirection = DirectX::XMVector3Normalize(rayDirection);  

	DirectX::XMVECTOR finalDirection = DirectX::XMVectorAdd(zDirection, rayDirection);
	finalDirection = DirectX::XMVector3Normalize(finalDirection);

	Vector3D finalDirVector = Vector3D(DirectX::XMVectorGetX(finalDirection),
		DirectX::XMVectorGetY(finalDirection),
		DirectX::XMVectorGetZ(finalDirection));

	return Ray(localPosition, finalDirVector);
}

Vector3D Camera::screenToWorldCoordinates(const Vector2D& screenPos)
{
	RECT rc = AppWindow::getInstance()->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	float xNDC = (screenPos.x / width) * 2.0f - 1.0f;
	float yNDC = 1.0f - (screenPos.y / height) * 2.0f;

	DirectX::XMVECTOR clipSpacePos = DirectX::XMVectorSet(xNDC, yNDC, -1.0f, 1.0f);  

	DirectX::XMMATRIX invProj = DirectX::XMMatrixInverse(nullptr,
		DirectX::XMMatrixSet(
			projection.mat[0][0], projection.mat[0][1], projection.mat[0][2], projection.mat[0][3],  
			projection.mat[1][0], projection.mat[1][1], projection.mat[1][2], projection.mat[1][3],  
			projection.mat[2][0], projection.mat[2][1], projection.mat[2][2], projection.mat[2][3],  
			projection.mat[3][0], projection.mat[3][1], projection.mat[3][2], projection.mat[3][3]   
		));

	DirectX::XMVECTOR viewSpacePos = DirectX::XMVector3TransformCoord(clipSpacePos, invProj);

	DirectX::XMMATRIX viewMatrix = DirectX::XMMatrixSet(
		localMatrix.mat[0][0], localMatrix.mat[0][1], localMatrix.mat[0][2], localMatrix.mat[0][3],  
		localMatrix.mat[1][0], localMatrix.mat[1][1], localMatrix.mat[1][2], localMatrix.mat[1][3], 
		localMatrix.mat[2][0], localMatrix.mat[2][1], localMatrix.mat[2][2], localMatrix.mat[2][3], 
		localMatrix.mat[3][0], localMatrix.mat[3][1], localMatrix.mat[3][2], localMatrix.mat[3][3]   
	);

	DirectX::XMMATRIX invView = DirectX::XMMatrixInverse(nullptr, viewMatrix);

	DirectX::XMVECTOR worldSpacePos = DirectX::XMVector3TransformCoord(viewSpacePos, invView);

	Vector3D worldPos = Vector3D(DirectX::XMVectorGetX(worldSpacePos),
						DirectX::XMVectorGetY(worldSpacePos),
						0.0f); 

	return worldPos;
}

void Camera::pickObject(const Vector2D& mousePos)
{
	//Ray ray = screenToWorldRay(mousePos);

	//for (GameObject* obj : GameObjectManager::getInstance()->getAllObjects())
	//{
	//	Drawable* drawable = dynamic_cast<Drawable*>(obj);
	//	if (drawable && ray.intersects(drawable->getBoundingBox())) 
	//	{
	//		std::cout << "Selected: " << drawable->getName() << std::endl;
	//		break;
	//	}

	//}

	Vector3D worldPos = screenToWorldCoordinates(mousePos);

	std::cout << worldPos.x << ", " << worldPos.y << std::endl;

	for (GameObject* obj : GameObjectManager::getInstance()->getAllObjects())
	{
		Drawable* drawable = dynamic_cast<Drawable*>(obj);
		if (drawable)
		{
			BoundingBox boundingBox = drawable->getBoundingBox();

			Vector3D min = boundingBox.min;
			Vector3D max = boundingBox.max;

			if (worldPos.x >= min.x && worldPos.x <= max.x &&
				worldPos.y >= min.y && worldPos.y <= max.y)
			{
				std::cout << "Selected: " << drawable->getName() << std::endl;
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
}

void Camera::onLeftMouseDown(const Vector2D& deltaPos)
{
	this->pickObject(deltaPos);
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

