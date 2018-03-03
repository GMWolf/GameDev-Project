#include "EntityManager.h"



EntityManager::EntityManager()
{
}


EntityManager::~EntityManager()
{
}

void EntityManager::update()
{
	for (int id : limbo) {
		aspects.erase(id);
		ids.push_back(id);
	}
	limbo.clear();
}


inline int EntityManager::getNewId() {
	if (!ids.empty()) {
		int _id = ids.front();
		ids.pop_front();
		return _id;
	}

	return nextID++;
}

Aspect & EntityManager::getAspect(int entity)
{
	return aspects.at(entity);
}

int EntityManager::createEntity()
{
	int id = getNewId();
	aspects.put(id, Aspect());
	return id;
}

void EntityManager::destroyEntity(int entityId)
{
	limbo.push_back(entityId);
}
