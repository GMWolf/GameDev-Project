#include "PhysicsColliderSystem.h"
#include "BulletCollision/CollisionShapes/btBoxShape.h"
#include "BulletCollision/CollisionShapes/btSphereShape.h"


PhysicsColliderSystem::PhysicsColliderSystem()
{
}


PhysicsColliderSystem::~PhysicsColliderSystem()
{
}

void PhysicsColliderSystem::init()
{
}

void PhysicsColliderSystem::update()
{
	while(!boxColliderInserted.events.empty())
	{
		auto& e = boxColliderInserted.events.front();

		glm::vec3& v = e.entity.get<BoxCollider>().halfSides;
		btCollisionShape* c = new btBoxShape(btVector3(v.x, v.y, v.z));

		e.entity.add(Collider(c));

		boxColliderInserted.events.pop();
	}

	while(!boxColliderRemoved.events.empty())
	{
		auto& e = boxColliderRemoved.events.front();

		delete e.entity.get<Collider>().collisionShape;
		e.entity.remove<Collider>();

		boxColliderRemoved.events.pop();
	}

	while (!sphereColliderInserted.events.empty())
	{
		auto& e = sphereColliderInserted.events.front();

		float r = e.entity.get<SphereCollider>().radius;
		btCollisionShape* c = new btSphereShape(r);

		e.entity.add(Collider(c));

		boxColliderInserted.events.pop();
	}

	while (!sphereColliderRemoved.events.empty())
	{
		auto& e = sphereColliderRemoved.events.front();

		delete e.entity.get<Collider>().collisionShape;
		e.entity.remove<Collider>();

		sphereColliderRemoved.events.pop();
	}
	
}

void PhysicsColliderSystem::end()
{
}
