#include "SystemManager.h"



void SystemManager::update()
{
	for (System* system : systems) {
		system->update();
		
	}
}
