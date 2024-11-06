#pragma once
#include "GameObject.h"
#include "InputListener.h"
#include "Ray.h"

class Camera : public GameObject, public InputListener
{

public:
	Camera(std::string name = "Camera");
	~Camera();

public:
	virtual void onCreate() override;
	virtual void onUpdate(float deltatime) override;
	virtual void onDestroy() override;

private:
	void updateViewMatrix();

	Ray screenToWorldRay(const Vector2D& screenPos);
	Vector3D screenToWorldCoordinates(const Vector2D& screenPos);

	void pickObject(const Vector2D& mousePos);

public:
	Matrix4x4 getViewMatrix();
	Matrix4x4 getProjectionMatrix();

public:
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Vector2D& deltaPos) override;
	virtual void onLeftMouseDown(const Vector2D& deltaPos) override;
	virtual void onLeftMouseUp(const Vector2D& deltaPos) override;
	virtual void onRightMouseDown(const Vector2D& deltaPos) override;
	virtual void onRightMouseUp(const Vector2D& deltaPos) override;


private:
	bool mouseDown = false;
	bool mouseDownLeft = false;

	Matrix4x4 projection;

public:
	float forward = 0.0f;
	float rightward = 0.0f;
	float upward = 0.0f;

};

