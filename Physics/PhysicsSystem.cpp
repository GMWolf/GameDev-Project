#include "PhysicsSystem.h"
#include "../Wagl/DeltaTime.h"
#include <iostream>


PhysicsSystem::PhysicsSystem() :
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
	while(!colliderInserted.events.empty())
	{
		auto& e = colliderInserted.events.front();

		addEntity(e.entity);

		colliderInserted.events.pop();
	}

	btTransform trans;

	for(Entity e : rigidBodies)
	{
		Transform& t = e.get<Transform>();
		RigidBody& rb = e.get<RigidBody>();

		rb.rigidBody->getMotionState()->getWorldTransform(trans);

		btVector3& pos = trans.getOrigin();
		btMatrix3x3& basis = trans.getBasis();
		t.position = Vector3(pos.x(), pos.y(), pos.z());

		btVector3 c0 = basis.getColumn(0);
		t.rotation.c0.xyz = Vector3(c0.x(), c0.y(), c0.z()).xyz;

		btVector3 c1 = basis.getColumn(1);
		t.rotation.c1.xyz = Vector3(c1.x(), c1.y(), c1.z()).xyz;

		btVector3 c2 = basis.getColumn(2);
		t.rotation.c2.xyz = Vector3(c2.x(), c2.y(), c2.z()).xyz;
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

void PhysicsSystem::RayCastClosest(Vector3 start, Vector3 end, Hit& hit)
{
	const btVector3 btStart(start.x, start.y, start.z);
	const btVector3 btEnd(end.x, end.y, end.z);
	btCollisionWorld::ClosestRayResultCallback callback(btStart, btEnd);

	dynamicsWorld->rayTest(btStart, btEnd, callback);

	assignBt(hit.worldPos, callback.m_hitPointWorld);
	assignBt(hit.normal, callback.m_hitNormalWorld);
	hit.hasHit = callback.hasHit();
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
	dynamicsWorld->addRigidBody(rb);
	std::cout << "entity " << entity.getId() << " is now an RB!" << std::endl;
}
