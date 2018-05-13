#include "BulletSystem.h"
#include "SubscriptionManager.h"
#include "Transform.h"
#include "VelocitySystem.h"
#include "CommonComponentLoader.h"
#include "SystemManager.h"
#include "Lights.h"
#include "LightFade.h"


BulletSystem::BulletSystem() : 
bullets(ECS::SubscriptionManager::getSubscription(ECS::Aspect::getAspect<Bullet, Transform, Velocity>()))
{
}


BulletSystem::~BulletSystem()
{
}

void BulletSystem::init()
{
	ECS::registerLoader<Bullet>(new CommonComponentLoader<Bullet>);

	physics = ECS::SystemManager::getSystem<PhysicsSystem>();
}

void BulletSystem::update()
{
	for (ECS::Entity bullet : bullets)
	{
		Transform& t = bullet.get<Transform>();
		Velocity& v = bullet.get<Velocity>();

		glm::vec3 from = t.position;
		glm::vec3 to = t.position + (v.v * (float)wagl::DeltaTime::delta);

		PhysicsSystem::Hit hit;
		physics->RayCastClosest(from, to, hit);
		if (hit.hasHit)
		{

			ECS::Entity e = ECS::Entity::create();
			e.add(Transform());
			e.get<Transform>().position = hit.worldPos + (hit.normal * 0.1f);
			e.add(PointLight(glm::vec3(0, 0.25, 1), 20, 3 * bullet.get<Bullet>().damage));
			e.add(LightFade(120));
			e.get<LightFade>().destroyOnEnd = true;

			ECS::Entity::destroy(bullet);
		}
	}
}

void BulletSystem::end()
{
}
