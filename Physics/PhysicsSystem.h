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

	struct Hit
	{
		Vector3 worldPos;
		bool hasHit;
		Vector3 normal;
	};

	void RayCastClosest(Vector3 start, Vector3 end, Hit& hit);

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

inline void assignBt(Vector3& v, const btVector3 rhs)
{
	v.x = rhs.x();
	v.y = rhs.y();
	v.z = rhs.z();
}

inline void assignVector(btVector3& v, const Vector3 rhs)
{
	v.setX(rhs.x);
	v.setY(rhs.y);
	v.setZ(rhs.z);
}