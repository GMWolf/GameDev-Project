#include "MovementSystem.h"
#include "SubscriptionManager.h"
#include "Transform.h"
#include "DeltaTime.h"
#include <iostream>
#include "VelocitySystem.h"
#include "Lights.h"
#include "SystemManager.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "MeshFilter.h"
#include "LightFade.h"
#include "ECS.h"
#include "CommonComponentLoader.h"

PlayerControlSystem::PlayerControlSystem():
	playerControled(ECS::SubscriptionManager::getSubscription(ECS::Aspect::getAspect<PlayerControl, Transform>())), ui(nullptr),
	physics(nullptr)
{
}

PlayerControlSystem::~PlayerControlSystem()
{
}

void PlayerControlSystem::init()
{
	ECS::registerLoader<PlayerControl>(new CommonComponentLoader<PlayerControl>());
	ui = ECS::SystemManager::getSystem<UISystem>();

	physics = ECS::SystemManager::getSystem<PhysicsSystem>();
	physics->registerTickCallback(this);
}

void PlayerControlSystem::update()
{
}

void PlayerControlSystem::end()
{
}

void PlayerControlSystem::tickCallback(btScalar timestep)
{
}

void PlayerControlSystem::pretickCallback(btScalar timestep)
{
	for (ECS::Entity e : playerControled)
	{
		PlayerControl& pc = e.get<PlayerControl>();

		Input* horizontal = ui->getInput(pc.horizontal);
		Input* vertical = ui->getInput(pc.vertical);


		Transform& t = e.get<Transform>();
		btRigidBody* rb = e.get<RigidBody>().rigidBody;

		btVector3 targetVelocity;
		targetVelocity += btVector3(t.rotation[2].x, t.rotation[2].y, t.rotation[2].z) * (*vertical)() * pc.speed;
		targetVelocity += btVector3(t.rotation[0].x, t.rotation[0].y, t.rotation[0].z) * (*horizontal)() * pc.speed;

		const btVector3 velocity = rb->getVelocityInLocalPoint(btVector3(0, 0, 0));
		btVector3 velocityDelta = targetVelocity - velocity;
		velocityDelta.setY(0);
		const float l = velocityDelta.norm();
		if (l > pc.maxChange)
		{
			velocityDelta.normalize();
			velocityDelta *= pc.maxChange;
		}

		rb->applyCentralForce((velocityDelta / rb->getInvMass()));

	}
}
