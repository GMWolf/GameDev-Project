#pragma once
#include <vector>
#include "System.h"
#include "Entity.h"
#include "SubscriptionManager.h"
#include <typeindex>

class SystemManager
{
public:
	
	static void update();

	static void init();
	static void end();
	
	static void addSystem(System* system);

	template<class T>
	static T* getSystem();

	static std::vector<System*> systems;
	
	static void setEnabled(System* system, bool enable);
	static bool isEnabled(System* system);

private:
	static std::map<std::type_index, System*> systemMap;

};

template <class T>
T* SystemManager::getSystem()
{
	return static_cast<T*>(systemMap.at(typeid(T)));
}

