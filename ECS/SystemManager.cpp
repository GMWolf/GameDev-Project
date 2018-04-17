#include "SystemManager.h"
#include <chrono>
#include <iostream>

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
			const auto start = std::chrono::high_resolution_clock::now();
			auto pureEnd = start;
			if (system->enabled) {
				system->update();

				pureEnd = std::chrono::high_resolution_clock::now();

				SubscriptionManager::update();
				Entity::entityManager.update();
			}
			const auto end = std::chrono::high_resolution_clock::now();
			system->lastPureTime = (float)std::chrono::duration_cast<std::chrono::microseconds>(pureEnd - start).count();
			system->lastTotalTime = (float)std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
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
