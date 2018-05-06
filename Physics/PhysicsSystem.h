#pragma once
#include <btBulletDynamicsCommon.h>

#include <System.h>
#include "EntityEvents.h"
#include "PhysicsColliderSystem.h"
#include <Transform.h>
#include "ITickCallback.h"

class PhysicsSystem : public ECS::System
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
		ECS::Entity entity;
	};

	void RayCastClosest(const glm::vec3 start, const glm::vec3 end, Hit& hit);

	EVENT(Impulse)
	{
		Impulse(): entity(-1), impulse(0,0,0)
		{
		}
		Impulse(ECS::Entity& entity, const glm::vec3& impulse, const glm::vec3& relPos)
		: entity(entity), impulse(impulse), relPos(relPos)
		{
		}

		ECS::Entity entity;
		glm::vec3 impulse;
		glm::vec3 relPos;
	};


	void tickCallback(btScalar timestep);
	void pretickCallback(btScalar timestep);

	void registerTickCallback(ITickCallback* callback);

private:
	btBroadphaseInterface * broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;

	ECS::EntitySubscription& rigidBodies;

	ECS::EventQueue<ECS::EntityInserted<Transform, Collider>> colliderInserted;
	ECS::EventQueue<Impulse> impulseEvents;


	void addEntity(ECS::Entity& entity);
	void HandleColliderInserts();
	void HandleEvents();
	void HandleImpulseEvents();

	std::vector<ITickCallback*> tickCallbacks;

};

inline void assignBt(glm::vec3& v, const btVector3& rhs)
{
	v.x = rhs.x();
	v.y = rhs.y();
	v.z = rhs.z();
}

inline void assignVector(btVector3& v, const glm::vec3& rhs)
{
	v.setX(rhs.x);
	v.setY(rhs.y);
	v.setZ(rhs.z);
}

inline void globalTickCallback(btDynamicsWorld* world, btScalar timestep)
{
	static_cast<PhysicsSystem*>(world->getWorldUserInfo())->tickCallback(timestep);
}

inline void globalPretickCallback(btDynamicsWorld* world, btScalar timestep)
{
	static_cast<PhysicsSystem*>(world->getWorldUserInfo())->pretickCallback(timestep);
}