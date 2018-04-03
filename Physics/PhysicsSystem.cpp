#include "PhysicsSystem.h"
#include "../Wagl/DeltaTime.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat.hpp>

PhysicsSystem::PhysicsSystem() : broadphase(nullptr), collisionConfiguration(nullptr), dispatcher(nullptr),
                                 solver(nullptr), dynamicsWorld(nullptr),
                                 rigidBodies(SubscriptionManager::getSubscription(Aspect::getAspect<RigidBody, Transform>()))
{
}


PhysicsSystem::~PhysicsSystem()
{
}

void PhysicsSystem::init()
{
	broadphase = new btDbvtBroadphase();
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	solver = new btSequentialImpulseConstraintSolver;
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0, -5, 0));

}

void PhysicsSystem::update()
{
	HandleEvents();
	btTransform trans;

	for(Entity e : rigidBodies)
	{
		Transform& t = e.get<Transform>();
		RigidBody& rb = e.get<RigidBody>();

		rb.rigidBody->getMotionState()->getWorldTransform(trans);

		btVector3& pos = trans.getOrigin();
		btMatrix3x3& basis = trans.getBasis();
		t.position = glm::vec3(pos.x(), pos.y(), pos.z());
		basis.getOpenGLSubMatrix(glm::value_ptr(t.rotation));
	}

	dynamicsWorld->stepSimulation(wagl::DeltaTime::delta, 10);
}

void PhysicsSystem::end()
{

	//Deletion order is important
	delete dynamicsWorld;
	delete solver;
	delete dispatcher;
	delete collisionConfiguration;
	delete broadphase;
}

void PhysicsSystem::RayCastClosest(const glm::vec3 start, const glm::vec3 end, Hit& hit)
{
	const btVector3 btStart(start.x, start.y, start.z);
	const btVector3 btEnd(end.x, end.y, end.z);
	btCollisionWorld::ClosestRayResultCallback callback(btStart, btEnd);

	dynamicsWorld->rayTest(btStart, btEnd, callback);

	assignBt(hit.worldPos, callback.m_hitPointWorld);
	assignBt(hit.normal, callback.m_hitNormalWorld);
	if((hit.hasHit = callback.hasHit()))
	{
		hit.entity = callback.m_collisionObject->getUserIndex();
	}
}

void PhysicsSystem::addEntity(Entity& entity)
{
	Transform& t = entity.get<Transform>();

	float mass = 0;

	if (entity.has<RigidBodyProperties>())
	{
		mass = entity.get<RigidBodyProperties>().mass;
	}

	btCollisionShape* shape = entity.get<Collider>().collisionShape;

	btVector3 inertia(0, 0, 0);
	shape->calculateLocalInertia(mass, inertia);
	
	btDefaultMotionState* ms = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(t.position.x, t.position.y, t.position.z)));
	btRigidBody::btRigidBodyConstructionInfo ci(mass, ms, shape, inertia);

	btRigidBody* rb = new btRigidBody(ci);

	entity.add(RigidBody(rb));
	rb->setUserIndex(entity.getId());
	dynamicsWorld->addRigidBody(rb);
}

void PhysicsSystem::HandleColliderInserts()
{
	while (!colliderInserted.events.empty())
	{
		auto& e = colliderInserted.events.front();

		addEntity(e.entity);

		colliderInserted.events.pop();
	}
}

void PhysicsSystem::HandleEvents()
{
	HandleImpulseEvents();
	HandleColliderInserts();
}

void PhysicsSystem::HandleImpulseEvents()
{
	btVector3 btImpulse, btRelPos;
	while(!impulseEvents.empty())
	{
		Impulse& i = impulseEvents.front();


		Entity e = i.entity;
		
		if (e.has<RigidBody>())
		{
			assignVector(btImpulse, i.impulse);
			assignVector(btRelPos, i.relPos);
			
			RigidBody& rb = e.get<RigidBody>();

			rb.rigidBody->activate(true);
			rb.rigidBody->applyImpulse(btImpulse, btRelPos);
		} else
		{
			std::cout << "Warning: entity does not have rigid body to apply impulse to" << "\n";
		}

		impulseEvents.pop();
	}
}
