#pragma once
#include "GameObject.h"

class Camera : public GameObject
{

public:
	Camera();
	Camera(std::string name);
	~Camera() {};

public:
	virtual void onCreate() override;
	virtual void onUpdate(float deltatime) override;
	virtual void onDestroy() override;

public:
	void updateMatrix();
	constant getUpdatedConstantData();

private:
	constant cc;

};

