#pragma once
#include <vector>
#include "System.h"
#include "Entity.h"
#include "SubscriptionManager.h"
class SystemManager
{
public:
	
	static void update();

	
	static void addSystem(System* system);

	static std::vector<System*> systems;

};

