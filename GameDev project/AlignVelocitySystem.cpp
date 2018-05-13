#include "AlignVelocitySystem.h"
#include "SubscriptionManager.h"
#include "Transform.h"
#include "VelocitySystem.h"
#include "CommonComponentLoader.h"
#include <glm/gtx/quaternion.hpp>

AlignVelocitySystem::AlignVelocitySystem() : entities(ECS::SubscriptionManager::getSubscription(ECS::Aspect::getAspect<Transform, Velocity, AlignToVelocity>()))
{
}


AlignVelocitySystem::~AlignVelocitySystem()
{
}

void AlignVelocitySystem::init()
{
	ECS::registerLoader<AlignToVelocity>(new CommonComponentLoader<AlignToVelocity>);
}

void AlignVelocitySystem::update()
{
	for(ECS::Entity e: entities)
	{
		if (e.get<AlignToVelocity>().align)
		{
			Transform& t = e.get<Transform>();
			Velocity& v = e.get<Velocity>();

			glm::vec3 dir = glm::normalize(v.v);

			/*glm::vec3 r(0,0,1);
			
			glm::vec3 T = glm::normalize(glm::cross(dir, r));
			glm::vec3 N = glm::normalize(glm::cross(T, dir));

			t.rotation[0] = glm::vec4(N, 0.0f);
			t.rotation[1] = glm::vec4(T, 0.0f);
			t.rotation[2] = glm::vec4(dir, 0.0f);*/

			auto q = glm::quat(glm::vec3(0, 0, 1), dir);
			t.rotation = glm::toMat4(q);
			

		}
	}
}

void AlignVelocitySystem::end()
{
}
