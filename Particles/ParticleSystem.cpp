#include "ParticleSystem.h"
#include "SubscriptionManager.h"
#include "Transform.h"
#include "Particle.h"
#include "DeltaTime.h"
#include "ParticleSpawner.h"
#include "AssetsComponentLoader.h"
#include "CommonComponentLoader.h"

ParticleSystem::ParticleSystem(Assets& assets): assets(assets),
particles(ECS::SubscriptionManager::getSubscription(ECS::Aspect::getAspect<Transform, Particle>())),
spawners(ECS::SubscriptionManager::getSubscription(ECS::Aspect::getAspect<Transform, ParticleSpawner>()))
{
}


ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::init()
{
	ECS::registerLoader<ParticleSpawner>(new AssetsComponentLoader<ParticleSpawner>(assets));
	ECS::registerLoader<Particle>(new CommonComponentLoader<Particle>);
}

void ParticleSystem::update()
{
	for(ECS::Entity e : particles)
	{
		Transform& t = e.get<Transform>();
		Particle& p = e.get<Particle>();

		p.velocity += p.gravity * (float)wagl::DeltaTime::delta;
		t.position += p.velocity * (float)wagl::DeltaTime::delta;
		p.life -= wagl::DeltaTime::delta;
		if (p.life <= 0)
		{
			ECS::Entity::destroy(e);
		}
	}

	for(ECS::Entity e : spawners)
	{
		Transform& t = e.get<Transform>();
		ParticleSpawner& sp = e.get<ParticleSpawner>();

		sp.carry += wagl::DeltaTime::delta;
		float invRate = 1 / sp.rate;
		while(sp.carry >= invRate)
		{
			sp.carry -= invRate;
			ECS::Entity ep = ECS::Entity::create(assets.resolve(sp.prefab));
			ep.get<Transform>().position = t.getPosition();
			Particle& p = ep.get<Particle>();
			p.velocity = sp.velocity;
			p.gravity = sp.gravity;
			p.life = sp.life;
		}
	}
}

void ParticleSystem::end()
{
}
