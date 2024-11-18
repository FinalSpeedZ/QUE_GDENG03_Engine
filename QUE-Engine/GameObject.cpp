#include "GameObject.h"

#include <reactphysics3d/mathematics/Quaternion.h>

GameObject::GameObject(std::string name)
{
	this->name = name;
	this->localPosition = Vector3D::zeroes;
	this->localRotation = Vector3D::zeroes;
	this->localScale = Vector3D::ones;

	this->localMatrix.setIdentity();

	this->computeLocalMatrix();

	active = true;
}

std::string GameObject::getName()
{
	return this->name;
}

void GameObject::setName(std::string name)
{
	this->name = name;
}

bool GameObject::isActive()
{
	return this->active;
}

void GameObject::setActive(bool active)
{
	this->active = active;
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

Matrix4x4 GameObject::getLocalMatrix()
{
	return this->localMatrix;
}


float* GameObject::getPhysicsLocalMatrix()
{
	Matrix4x4 transform;
	Matrix4x4 scaleMatrix;
	Matrix4x4 rotationMatrix;
	Matrix4x4 translationMatrix;
	Matrix4x4 temp;

	transform.setIdentity();

	scaleMatrix.setIdentity();
	scaleMatrix.setScale(Vector3D::ones);

	rotationMatrix.setIdentity();

	temp.setIdentity();
	temp.setRotationZ(this->localRotation.z);
	rotationMatrix *= temp;

	temp.setIdentity();
	temp.setRotationY(this->localRotation.y);
	rotationMatrix *= temp;

	temp.setIdentity();
	temp.setRotationX(this->localRotation.x);
	rotationMatrix *= temp;

	translationMatrix.setIdentity();
	translationMatrix.setTranslation(this->localPosition);

	transform = scaleMatrix * rotationMatrix * translationMatrix;

	return transform.getMatrix();
}

void GameObject::recomputeMatrix(float matrix[16])
{
	float matrix4x4[4][4];
	matrix4x4[0][0] = matrix[0];
	matrix4x4[0][1] = matrix[1];
	matrix4x4[0][2] = matrix[2];
	matrix4x4[0][3] = matrix[3];

	matrix4x4[1][0] = matrix[4];
	matrix4x4[1][1] = matrix[5];
	matrix4x4[1][2] = matrix[6];
	matrix4x4[1][3] = matrix[7];

	matrix4x4[2][0] = matrix[8];
	matrix4x4[2][1] = matrix[9];
	matrix4x4[2][2] = matrix[10];
	matrix4x4[2][3] = matrix[11];

	matrix4x4[3][0] = matrix[12];
	matrix4x4[3][1] = matrix[13];
	matrix4x4[3][2] = matrix[14];
	matrix4x4[3][3] = matrix[15];

	Matrix4x4 newMatrix;
	newMatrix.setMatrix(matrix4x4);

	Matrix4x4 scaleMatrix;
	scaleMatrix.setScale(this->localScale);
	Matrix4x4 transMatrix;
	transMatrix.setTranslation(this->localPosition);

	this->localMatrix = scaleMatrix * transMatrix * newMatrix;
	this->overrideMatrix = true;
}

void GameObject::computeLocalMatrix()
{
	Matrix4x4 transform;
	Matrix4x4 scaleMatrix;
	Matrix4x4 rotationMatrix;
	Matrix4x4 translationMatrix;
	Matrix4x4 temp;

	transform.setIdentity();

	scaleMatrix.setIdentity();
	scaleMatrix.setScale(this->localScale);

	rotationMatrix.setIdentity();

	temp.setIdentity();
	temp.setRotationZ(this->localRotation.z);
	rotationMatrix *= temp;

	temp.setIdentity();
	temp.setRotationY(this->localRotation.y);
	rotationMatrix *= temp;

	temp.setIdentity();
	temp.setRotationX(this->localRotation.x);
	rotationMatrix *= temp;

	translationMatrix.setIdentity();
	translationMatrix.setTranslation(this->localPosition);

	transform = scaleMatrix * rotationMatrix * translationMatrix;

	this->localMatrix = transform;
}

void GameObject::attachComponent(Component* component)
{
	this->componentList.push_back(component);
	component->attachOwner(this);
}

void GameObject::detachComponent(Component* component)
{
	int index = -1;

	for (int i = 0; i < this->componentList.size(); i++) 
	{
		if (this->componentList[i] == component)
		{
			index = i;
			break;
		}
	}

	if (index != -1)
	{
		this->componentList.erase(this->componentList.begin() + index);
	}
}

Component* GameObject::findComponentByName(std::string name)
{
	for (int i = 0; i < this->componentList.size(); i++) 
	{
		if (this->componentList[i]->getName() == name) 
		{
			return this->componentList[i];
		}
	}

	return NULL;
}

Component* GameObject::findComponentOfType(ComponentType type, std::string name)
{
	for (int i = 0; i < this->componentList.size(); i++) 
	{
		if (this->componentList[i]->getName() == name && this->componentList[i]->getType() == type)
		{
			return this->componentList[i];
		}
	}

	return NULL;
}

std::vector<Component*> GameObject::getComponentsOfType(ComponentType type)
{
	std::vector<Component*> components;

	for (int i = 0; i < this->componentList.size(); i++) 
	{
		if (this->componentList[i]->getType() == type)
		{
			components.push_back(this->componentList[i]);
		}
	}

	return components;
}

void GameObject::onUpdate(float deltatime)
{
	if (firstTime)
	{
		this->onCreate();
		firstTime = false;
	}
}

void GameObject::onDestroy()
{
	delete this;
}


