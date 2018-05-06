#include "FPSCameraSystem.h"
#include "CommonComponentLoader.h"
#include "SystemManager.h"
#include "PhysicsComponents.h"


FPSCameraSystem::FPSCameraSystem() : 
entities(ECS::SubscriptionManager::getSubscription(ECS::Aspect::getAspect<Transform, FPSCamera>()))
{
}


FPSCameraSystem::~FPSCameraSystem()
{
}

void FPSCameraSystem::init()
{
	ECS::registerLoader<FPSCamera>(new CommonComponentLoader<FPSCamera>);

	uisystem = ECS::SystemManager::getSystem<UISystem>();
}

void FPSCameraSystem::update()
{
	for(ECS::Entity e : entities)
	{
		FPSCamera& c = e.get<FPSCamera>();
		Transform& t = e.get<Transform>();

		Input* horizontal = uisystem->getInput(c.horizontal);
		Input* vertical = uisystem->getInput(c.vertical);

		//vertical only affects camera
		t.rotation = glm::rotate(glm::mat4(1), (*vertical)() / 500, glm::vec3(t.rotation[0])) * t.rotation;

		//horizontal affects body
		RigidBody& body = c.body.get<RigidBody>();
		body.rigidBody->setAngularVelocity(btVector3(0, (*horizontal)() * -0.2, 0));
		
	}
}

void FPSCameraSystem::end()
{
}
