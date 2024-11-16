#include "PhysicsComponent.h"

#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"
#include "GameObject.h"
#include "Vector3D.h"

PhysicsComponent::PhysicsComponent(std::string name, GameObject* owner)
	: Component(name, ComponentType::Physics, owner)
{
	BaseComponentSystem::getInstance()->getPhysicsSystem()->registerComponent(this);
	PhysicsCommon* physicsCommon = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsCommon();
	PhysicsWorld* physicsWorld = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsWorld();

	Vector3D scale = this->getOwner()->getLocalScale();

	Transform transform;
	transform.setFromOpenGL(this->getOwner()->getPhysicsLocalMatrix());

	BoxShape* boxShape = physicsCommon->createBoxShape(Vector3(scale.x, scale.y, scale.z));

	this->rigidBody = physicsWorld->createRigidBody(transform);
	this->rigidBody->addCollider(boxShape, transform);
	this->rigidBody->updateMassPropertiesFromColliders();
	this->rigidBody->setMass(this->mass);
	this->rigidBody->setType(BodyType::DYNAMIC);

	transform = this->rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	this->getOwner()->recomputeMatrix(matrix);
}

PhysicsComponent::~PhysicsComponent()
{
	Component::~Component();

	BaseComponentSystem::getInstance()->getPhysicsSystem()->unregisterComponent(this);
}

void PhysicsComponent::perform(float deltaTime)
{

	const Transform transform = this->rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	this->getOwner()->recomputeMatrix(matrix);
}

RigidBody* PhysicsComponent::getRigidBody()
{
	return rigidBody;
}
