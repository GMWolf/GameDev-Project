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
		Entity entity;
	};

	void RayCastClosest(const Vector3 start, const Vector3 end, Hit& hit);

	EVENT(Impulse)
	{
		Impulse(): entity(-1), impulse(0,0,0)
		{
		}
		Impulse(Entity& entity, const Vector3& impulse, const Vector3& relPos)
		: entity(entity), impulse(impulse), relPos(relPos)
		{
		}
		Entity entity;
		Vector3 impulse;
		Vector3 relPos;
	};

private:
	btBroadphaseInterface * broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;

	EntitySubscription& rigidBodies;

	EventQueue<EntityInserted<Transform, Collider>> colliderInserted;
	EventQueue<Impulse> impulseEvents;


	void addEntity(Entity& entity);
	void HandleColliderInserts();
	void HandleEvents();
	void HandleImpulseEvents();
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