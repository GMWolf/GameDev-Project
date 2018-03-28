#include "VelocitySystem.h"
VelocitySystem::VelocitySystem() :
	velE(SubscriptionManager::getSubscription(Aspect::getAspect<Velocity, Transform>()))
{
}

void VelocitySystem::init()
{
}


void VelocitySystem::update()
{
	for (Entity e : velE)
	{
		e.get<Transform>().position += e.get<Velocity>().v * (float)wagl::DeltaTime::delta;
	}
}

void VelocitySystem::end()
{
}
