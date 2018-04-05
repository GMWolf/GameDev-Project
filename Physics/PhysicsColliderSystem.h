#pragma once
#include "../ECS/EntityEvents.h"
#include "PhysicsComponents.h"
#include "../ECS/System.h"

class PhysicsColliderSystem : public System
{
public:
	PhysicsColliderSystem();
	~PhysicsColliderSystem();

	void init() override;
	void update() override;
	void end() override;

private:

	EventQueue<EntityInserted<BoxCollider>> boxColliderInserted;
	EventQueue<EntityRemoved<BoxCollider>> boxColliderRemoved;

	EventQueue<EntityInserted<SphereCollider>> sphereColliderInserted;
	EventQueue<EntityRemoved<SphereCollider>> sphereColliderRemoved;

	EventQueue<EntityInserted<CapsuleCollider>> capsuleColliderInserted;
	EventQueue<EntityRemoved<CapsuleCollider>> capsuleColliderRemoved;

	EventQueue<EntityInserted<MeshCollider>> meshColliderInserted;
	EventQueue<EntityRemoved<MeshCollider>> meshColliderRemoved;
	
};

