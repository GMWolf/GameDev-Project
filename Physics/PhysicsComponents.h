#pragma once
#include <Component.h>
#include <BulletCollision/CollisionShapes/btCollisionShape.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <Vector3.h>
#include <glm/glm.hpp>

COMPONENT(BoxCollider, 1)
{
	BoxCollider() : halfSides(1, 1, 1)
	{
	}

	BoxCollider(glm::vec3 hs) : halfSides(hs)
	{
	}

	glm::vec3 halfSides;
};

COMPONENT(SphereCollider, 1)
{
	SphereCollider() : radius(1)
	{
	}

	SphereCollider(float r) : radius(r)
	{
	}

	float radius;
};

COMPONENT(CapsuleCollider, 1)
{
	CapsuleCollider() : radius(1) , height(2)
	{
	}

	CapsuleCollider(float r, float height) : radius(r), height(height)
	{
	}

	float height;
	float radius;
};

COMPONENT(Collider, 16)
{

	Collider() : collisionShape(nullptr)
	{
	}

	Collider(btCollisionShape* s) : collisionShape(s)
	{
	}

	btCollisionShape* collisionShape;

};

COMPONENT(RigidBodyProperties, 16)
{
	RigidBodyProperties() : mass(1) {}

	RigidBodyProperties(float mass) : mass(mass){}

	float mass;
};

COMPONENT(RigidBody, 16)
{

	RigidBody() : rigidBody(nullptr)
	{
	}

	RigidBody(btRigidBody* r) : rigidBody(r)
	{
	}

	btRigidBody* rigidBody;

	glm::vec3 getCenterOfMassPosition()
	{
		auto& com = rigidBody->getCenterOfMassPosition();
		return glm::vec3(com.x(), com.y(), com.z());
	}
};
