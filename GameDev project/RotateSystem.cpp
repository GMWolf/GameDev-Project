#include "RotateSystem.h"



RotateSystem::RotateSystem(): entities(SubscriptionManager::getSubscription(Aspect::getAspect<Transform, Rotate>()))
{
}


RotateSystem::~RotateSystem()
{
}

void RotateSystem::init()
{

}

void RotateSystem::update()
{
	for(Entity e : entities)
	{
		Transform& t = e.get<Transform> ();
		const float rate = e.get<Rotate>().rate;
		t.rotation =glm::rotate(t.rotation, rate, glm::vec3(0, 1, 0));
	}
}

void RotateSystem::end()
{
}
