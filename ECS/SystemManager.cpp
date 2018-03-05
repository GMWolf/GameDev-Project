#include "SystemManager.h"



void SystemManager::update()
{
	for (System* system : systems) {
		system->update();
		SubscriptionManager::update();
		Entity::entityManager.update();
	}
}

void SystemManager::addSystem(System * system)
{
	systems.push_back(system);
}
