#pragma once
#include <btBulletDynamicsCommon.h>

#include "../ECS/System.h"

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


	btCollisionShape* groundShape;
	btCollisionShape* fallShape;
	btDefaultMotionState* groundMotionState;
	btRigidBody* groundRigidBody;
	btDefaultMotionState* fallMotionState;
	btRigidBody* fallRigidBody;
};

