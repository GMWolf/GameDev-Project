#include "LifeSystem.h"
#include "ECS.h"
#include "CommonComponentLoader.h"

LifeSystem::LifeSystem(): entities(ECS::SubscriptionManager::getSubscription(ECS::Aspect::getAspect<Life>()))
{
}

void LifeSystem::init()
{
	ECS::registerLoader<Life>(new CommonComponentLoader<Life>);
}

void LifeSystem::update()
{
	for (ECS::Entity e : entities)
	{
		Life& l = e.get<Life>();
		l.t -= wagl::DeltaTime::delta;
		if (l.t <= 0)
		{
			ECS::Entity::destroy(e);
		}
	}
}

void LifeSystem::end()
{
}
