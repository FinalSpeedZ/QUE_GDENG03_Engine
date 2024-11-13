#include "Bunny.h"

#include <corecrt_math_defines.h>
#include <iostream>
#include <list>

Bunny::Bunny(std::string name)
	: Drawable(name)
{
	this->localScale = Vector3D(10.0f);
}

void Bunny::onCreate()
{
	m_mesh = GraphicsEngine::getInstance()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\bunny.obj");
	Drawable::onCreate();
}

void Bunny::onUpdate(float deltaTime)
{
	Drawable::onUpdate(deltaTime);
}

void Bunny::onDestroy()
{
	Drawable::onDestroy();

}

void Bunny::draw()
{
	Drawable::draw();

}

void Bunny::updateConstantBuffer(float deltaTime)
{
	Drawable::updateConstantBuffer(deltaTime);
}

void Bunny::projectionViewMatrix()
{
	Drawable::projectionViewMatrix();
}



