#pragma once
#include <deque>
#include <HashedArrayTree.h>
#include "Aspect.h"

class EntityManager
{
	friend class Entity;

public:
	EntityManager();
	~EntityManager();
	
	void update();

	Aspect& getAspect(int entity);

private:
	int nextID;
	std::deque<int> ids;
	std::vector<int> limbo;
	HashedArrayTree<32, Aspect> aspects;

	int getNewId();
	int createEntity();
	void destroyEntity(int entityId);
};

