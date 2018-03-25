#pragma once
#include <btBulletDynamicsCommon.h>

#include <System.h>
#include "EntityEvents.h"
#include "PhysicsColliderSystem.h"
#include <Transform.h>

class PhysicsSystem : public System
{
public:
	PhysicsSystem();
	~PhysicsSystem();

	void init() override;
	void update() override;
	void end() override;

private:
	btBroadphaseInterface * broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;

	EntitySubscription& rigidBodies;

	EventQueue<EntityInserted<Transform, Collider>> colliderInserted;
	
	void addEntity(Entity& entity);
};

