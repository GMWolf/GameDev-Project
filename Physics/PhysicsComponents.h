#pragma once
#include <Component.h>
#include <BulletCollision/CollisionShapes/btCollisionShape.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <Vector3.h>

COMPONENT(BoxCollider, 1)
{
	BoxCollider() : halfSides(Vector3(1, 1, 1))
	{
	}

	BoxCollider(Vector3 hs) : halfSides(hs)
	{
	}

	Vector3 halfSides;
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
};
