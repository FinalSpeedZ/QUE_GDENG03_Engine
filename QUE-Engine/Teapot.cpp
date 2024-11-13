#include "Teapot.h"

#include <corecrt_math_defines.h>
#include <iostream>
#include <list>

#include "AppWindow.h"
#include "InputSystem.h"

Teapot::Teapot(std::string name)
	: Drawable(name)
{
}

void Teapot::onCreate()
{
	m_tex = TextureManager::getInstance()->createTextureFromFile(L"Assets\\Textures\\brick.png");
	m_mesh = GraphicsEngine::getInstance()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\teapot.obj");
	Drawable::onCreate();
}

void Teapot::onUpdate(float deltaTime)
{
	Drawable::onUpdate(deltaTime);
}

void Teapot::onDestroy()
{
	Drawable::onDestroy();
}

void Teapot::draw()
{
	Drawable::draw();

}

void Teapot::updateConstantBuffer(float deltaTime)
{
	Drawable::updateConstantBuffer(deltaTime);
}

void Teapot::projectionViewMatrix()
{
	Drawable::projectionViewMatrix();
}



