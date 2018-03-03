#pragma once
#include <vector>
#include <map>
#include "Aspect.h"
#include <Pool.h>
#include <DynBitset.h>

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

	void markDirty(int entityId);

	const Aspect aspect;
private:
	DynBitset dirtyEntityIds;
	DynBitset entityIds;
};
