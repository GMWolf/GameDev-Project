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
		
			//int id = lightWave::componentId.id;

			auto& pl = e.get<PointLight>();
			auto& lw = e.get<lightWave>();
			
			lw.off += lw.rate * wagl::DeltaTime::delta;

			//pl.power = lw.min + ((lw.max - lw.min) * (1 + sin(lw.off)) * 0.5f);
			pl.power = lw.min + (lw.max - lw.min) * (rand() / (float)RAND_MAX);
		
		}
	}
}

void LightWaveSystem::end()
{
}
