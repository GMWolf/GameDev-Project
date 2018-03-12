#pragma once
#include <vector>
#include "Aspect.h"
#include <DynBitset.h>

class EntitySubscriptionObserver
{
	
};

class EntitySubscription
{
public:

	EntitySubscription();
	EntitySubscription(Aspect aspect);

	std::vector<int> entities;
	void update();

	auto begin() {
		return entities.begin();
	}
	auto end() {
		return entities.end();
	}

	int getFirst()
	{
		return entities.at(0);
	}

	void markDirty(int entityId);

	const Aspect aspect;
private:
	DynBitset dirtyEntityIds;
	DynBitset entityIds;
};
