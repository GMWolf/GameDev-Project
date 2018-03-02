#include "EntityManager.h"



EntityManager::EntityManager()
{
}


EntityManager::~EntityManager()
{
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
	aspects.erase(entityId);
	ids.push_back(entityId);
}
