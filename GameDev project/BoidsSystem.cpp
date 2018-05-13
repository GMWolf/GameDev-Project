#include "BoidsSystem.h"
#include "SystemManager.h"
#include "Transform.h"
#include "glm/gtx/norm.hpp"
#include "VelocitySystem.h"
#include "CommonComponentLoader.h"

BoidsSystem::BoidsSystem() : boids(ECS::SubscriptionManager::getSubscription(ECS::Aspect::getAspect<Boid, Transform, Velocity>()))
{
}


BoidsSystem::~BoidsSystem()
{
}

void BoidsSystem::init()
{
	ECS::registerLoader<Boid>(new CommonComponentLoader<Boid>);
}

void BoidsSystem::update()
{

	for(ECS::Entity e : boids)
	{
		Transform& t = e.get<Transform>();
		glm::vec3 thisPos = t.getPosition();
		Boid& boid = e.get<Boid>();

		glm::vec3 sep;
		glm::vec3 center(0);
		int coheseCount = 0;
		glm::vec3 align(0);
		int alignCount = 0;
		for(ECS::Entity other : boids)
		{
			if (e == other) continue;
			Transform& ot = other.get<Transform>();
			glm::vec3 otherPos = ot.getPosition();
			glm::vec3 d = thisPos - otherPos;
			float dist2 = glm::length2(d);
			d = glm::normalize(d);
			if (dist2 < boid.separationRadius*boid.separationRadius)
			{
				sep += d / (sqrtf(dist2));
			}
			
			if (dist2 < boid.cohesionRadius*boid.cohesionRadius)
			{
				center += otherPos;
				coheseCount++;
			}

			if (dist2 < boid.alignmentRadius*boid.alignmentRadius)
			{
				align += other.get<Velocity>().v;
				alignCount++;
			}
		}

		center /= coheseCount;
		align /= alignCount;

		Velocity& vel = e.get<Velocity>();

		align = align - vel.v;

		glm::vec3 cohese = glm::normalize(center - thisPos);

		cohese *= boid.cohesionFactor *wagl::DeltaTime::delta;
		align *= boid.alignmentFactor *wagl::DeltaTime::delta;
		sep *= boid.separationFactor *wagl::DeltaTime::delta;
		
		
		vel.v += (cohese + align + sep);
		if (glm::length2(vel.v) >  boid.maxVelocity)
		{
			vel.v = glm::normalize(vel.v) * boid.maxVelocity;
		}

	}
}

void BoidsSystem::end()
{
}
