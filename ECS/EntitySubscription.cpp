#include "EntitySubscription.h"
#include "Entity.h"

EntitySubscription::EntitySubscription(Aspect aspect) : aspect(aspect) {
	entities.clear();
}

EntitySubscription::EntitySubscription() : aspect(0) {
	entities.clear();
}

void EntitySubscription::update()
{
	if (dirtyEntityIds.size() > 0) {
		for (int i = 0; i < dirtyEntityIds.size(); i++) {
			if (Entity(i).has(aspect)) {
				entityIds.set(i);
			}
			else {
				entityIds.reset(i);
			}
		}
		dirtyEntityIds.clear();

		entities.clear();
		for (int i = 0; i < entityIds.size(); i++) {
			if (entityIds[i]) {
				entities.push_back(i);
			}
		}
	}
}

void EntitySubscription::markDirty(int entityid)
{
	dirtyEntityIds.set(entityid);
}
