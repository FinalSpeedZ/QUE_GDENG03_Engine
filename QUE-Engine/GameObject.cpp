#include "GameObject.h"

GameObject::GameObject(std::string name)
{
	this->name = name;
	this->localPosition = Vector3D::zeroes;
	this->localRotation = Vector3D::zeroes;
	this->localScale = Vector3D::ones;
}

std::string GameObject::getName()
{
	return this->name;
}

void GameObject::setName(std::string name)
{
	this->name = name;
}

void GameObject::setPosition(float x, float y, float z)
{
	this->localPosition = Vector3D(x, y, z);
}

void GameObject::setPosition(Vector3D pos)
{
	this->localPosition = pos;
}

Vector3D GameObject::getLocalPosition()
{
	return this->localPosition;
}

void GameObject::setRotation(float x, float y, float z)
{
	this->localRotation = Vector3D(x, y, z);
}

void GameObject::setRotation(Vector3D rot)
{
	this->localRotation = rot;
}

void GameObject::setRotationX(float x)
{
	this->localRotation = Vector3D(x, this->localRotation.y, this->localRotation.z);
}

void GameObject::setRotationY(float y)
{
	this->localRotation = Vector3D(this->localRotation.x, y, this->localRotation.z);
}

void GameObject::setRotationZ(float z)
{
	this->localRotation = Vector3D(this->localRotation.x, this->localRotation.y, z);
}

Vector3D GameObject::getLocalRotation()
{
	return this->localRotation;
}

void GameObject::setScale(float x, float y, float z)
{
	this->localScale = Vector3D(x, y, z);
}

void GameObject::setScale(Vector3D scale)
{
	this->localScale = scale;
}

Vector3D GameObject::getLocalScale()
{
	return this->localScale;
}

void GameObject::onDestroy()
{
	delete this;
}


