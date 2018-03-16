#include "LightWaveSystem.h"
#include "SubscriptionManager.h"
#include "Lights.h"
#include "LightWave.h"
#include <Entity.h>
#include <DeltaTime.h>


LightWaveSystem::LightWaveSystem() : entities(SubscriptionManager::getSubscription(Aspect::getAspect<lightWave, PointLight>()))
{
}


LightWaveSystem::~LightWaveSystem()
{
}

void LightWaveSystem::init()
{
}

void LightWaveSystem::update()
{
	for (Entity e : entities) {

		if (e.has<lightWave>()) {
			auto pl = e.get<PointLight>();
			auto lw = e.get<lightWave>();

			pl.power = lw.min + (lw.max - lw.min) * sin(lw.rate * wagl::DeltaTime::delta);
		}
	}
}

void LightWaveSystem::end()
{
}
