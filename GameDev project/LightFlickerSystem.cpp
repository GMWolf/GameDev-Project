#include "LightFlickerSystem.h"
#include "SubscriptionManager.h"
#include "Lights.h"
#include "LightFlicker.h"
#include <Entity.h>
#include <DeltaTime.h>
#include "LightFlickerSystem.h"


LightFlickerSystem::LightFlickerSystem() : entities(SubscriptionManager::getSubscription(Aspect::getAspect<lightFlicker, PointLight>()))
{
}


LightFlickerSystem::~LightFlickerSystem()
{
}

void LightFlickerSystem::init()
{
}

void LightFlickerSystem::update()
{
	for (Entity e : entities) {

		if (e.has<lightFlicker>()) {
		
			//int id = lightFlicker::componentId.id;

			auto& pl = e.get<PointLight>();
			auto& lw = e.get<lightFlicker>();
			
			lw.off += lw.rate * wagl::DeltaTime::delta;

			//pl.power = lw.min + ((lw.max - lw.min) * (1 + sin(lw.off)) * 0.5f);
			pl.power = lw.min + (lw.max - lw.min) * (rand() / (float)RAND_MAX);
		
		}
	}
}

void LightFlickerSystem::end()
{
}
