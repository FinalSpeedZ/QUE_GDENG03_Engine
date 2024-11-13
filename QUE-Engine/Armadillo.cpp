#include "Armadillo.h"

#include <corecrt_math_defines.h>
#include <iostream>
#include <list>

Armadillo::Armadillo(std::string name)
	: Drawable(name)
{
}

void Armadillo::onCreate()
{
	m_mesh = GraphicsEngine::getInstance()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\armadillo.obj");
	Drawable::onCreate();
}

void Armadillo::onUpdate(float deltaTime)
{
	Drawable::onUpdate(deltaTime);
}

void Armadillo::onDestroy()
{
	Drawable::onDestroy();

}

void Armadillo::draw()
{
	Drawable::draw();

}

void Armadillo::updateConstantBuffer(float deltaTime)
{
	Drawable::updateConstantBuffer(deltaTime);
}

void Armadillo::projectionViewMatrix()
{
	Drawable::projectionViewMatrix();
}



