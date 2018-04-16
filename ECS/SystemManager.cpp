#include "SystemManager.h"
#include <chrono>

namespace ECS {

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
			auto start = std::chrono::high_resolution_clock::now();
			if (system->enabled) {
				system->update();

				SubscriptionManager::update();
				Entity::entityManager.update();
			}
			auto end = std::chrono::high_resolution_clock::now();
			system->lastTime = (float)std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
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
		systemMap.insert({ typeid(*system), system });
		system->enabled = true;
	}

	void SystemManager::setEnabled(System* system, bool enable)
	{
		system->enabled = enable;
	}

	bool SystemManager::isEnabled(System* system)
	{
		return system->enabled;
	}

}