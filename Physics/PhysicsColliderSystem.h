#pragma once
#include "../ECS/EntityEvents.h"
#include "PhysicsComponents.h"
#include "../ECS/System.h"

class PhysicsColliderSystem : public ECS::System
{
public:
	PhysicsColliderSystem();
	~PhysicsColliderSystem();

	void init() override;
	void update() override;
	void end() override;

private:

	ECS::EventQueue<ECS::EntityInserted<BoxCollider>> boxColliderInserted;
	ECS::EventQueue<ECS::EntityRemoved<BoxCollider>> boxColliderRemoved;

	ECS::EventQueue<ECS::EntityInserted<SphereCollider>> sphereColliderInserted;
	ECS::EventQueue<ECS::EntityRemoved<SphereCollider>> sphereColliderRemoved;

	ECS::EventQueue<ECS::EntityInserted<CapsuleCollider>> capsuleColliderInserted;
	ECS::EventQueue<ECS::EntityRemoved<CapsuleCollider>> capsuleColliderRemoved;

	ECS::EventQueue<ECS::EntityInserted<MeshCollider>> meshColliderInserted;
	ECS::EventQueue<ECS::EntityRemoved<MeshCollider>> meshColliderRemoved;
	
};

