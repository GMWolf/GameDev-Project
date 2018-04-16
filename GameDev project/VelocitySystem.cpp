#include "VelocitySystem.h"
VelocitySystem::VelocitySystem() :
	velE(ECS::SubscriptionManager::getSubscription(ECS::Aspect::getAspect<Velocity, Transform>()))
{
}

void VelocitySystem::init()
{
}


void VelocitySystem::update()
{
	for (ECS::Entity e : velE)
	{
		e.get<Transform>().position += e.get<Velocity>().v * (float)wagl::DeltaTime::delta;
	}
}

void VelocitySystem::end()
{
}
