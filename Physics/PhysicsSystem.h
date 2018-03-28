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
		glm::vec3 worldPos;
		bool hasHit;
		glm::vec3 normal;
		Entity entity;
	};

	void RayCastClosest(const glm::vec3 start, const glm::vec3 end, Hit& hit);

	EVENT(Impulse)
	{
		Impulse(): entity(-1), impulse(0,0,0)
		{
		}
		Impulse(Entity& entity, const glm::vec3& impulse, const glm::vec3& relPos)
		: entity(entity), impulse(impulse), relPos(relPos)
		{
		}
		Entity entity;
		glm::vec3 impulse;
		glm::vec3 relPos;
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

inline void assignBt(glm::vec3& v, const btVector3 rhs)
{
	v.x = rhs.x();
	v.y = rhs.y();
	v.z = rhs.z();
}

inline void assignVector(btVector3& v, const glm::vec3 rhs)
{
	v.setX(rhs.x);
	v.setY(rhs.y);
	v.setZ(rhs.z);
}