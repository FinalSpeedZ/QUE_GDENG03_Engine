#pragma once
#include "Drawable.h"

class Teapot : public Drawable
{
	
public:
	Teapot(std::string name = "Teapot");
	~Teapot() {};

public:
	void onCreate() override;
	void onUpdate(float deltaTime) override;
	void onDestroy() override;

protected:
	void draw() override;

private:
	void updateConstantBuffer(float deltaTime) override;
	void projectionViewMatrix() override;
};

