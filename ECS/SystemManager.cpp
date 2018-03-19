#include "SystemManager.h"


std::vector<System*> SystemManager::systems;
std::map<std::type_index, System*> SystemManager::systemMap;

void SystemManager::init() {
	for (System* system : systems) {
		system->init();
	}
}

void SystemManager::update()
{
	for (System* system : systems) {
		system->update();
		SubscriptionManager::update();
		Entity::entityManager.update();
	}
}

void SystemManager::end() {
	for (System* system : systems) {
		system->end();
	}
}

void SystemManager::addSystem(System * system)
{
	systems.push_back(system);
	systemMap.insert({typeid(*system), system});
}
