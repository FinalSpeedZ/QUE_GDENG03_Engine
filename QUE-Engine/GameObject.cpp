#include "GameObject.h"

GameObject::GameObject(std::string name)
{
	this->name = name;
	this->localPosition = Vector3D::zeroes;
	this->localRotation = Vector3D::zeroes;
	this->localScale = Vector3D::ones;
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
