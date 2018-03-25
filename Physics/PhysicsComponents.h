#pragma once
#include "../ECS/Component.h"
#include "BulletCollision/CollisionShapes/btCollisionShape.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"

COMPONENT(Collider, 16)
{
	btCollisionShape* collision_shape;

};

COMPONENT(RigidBody, 16)
{
	btRigidBody* rigidBody;
};
