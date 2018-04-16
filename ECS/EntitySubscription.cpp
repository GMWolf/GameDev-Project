#include "EntitySubscription.h"
#include "Entity.h"

namespace ECS {

	EntitySubscription::EntitySubscription(Aspect aspect) : entities(0), aspect(aspect)
	{
	}

	EntitySubscription::EntitySubscription() : aspect(0) {

	}

	void EntitySubscription::update()
	{
		if (dirtyEntityIds.size() > 0) {
			for (int i = 0; i < dirtyEntityIds.size(); i++) {

				if (dirtyEntityIds[i]) {
					if (Entity(i).has(aspect)) {
						if (!entityIds[i])
						{
							for (auto o : observers)
							{
								o->onInsert(i);
							}
						}
						entityIds.set(i);
					}
					else {
						if (entityIds[i])
						{
							for (auto o : observers)
							{
								o->onRemove(i);
							}
						}
						entityIds.reset(i);
					}
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

}