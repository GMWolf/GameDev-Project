#pragma once
#include <vector>
#include "Aspect.h"
#include <DynBitset.h>

namespace ECS {

	class EntitySubscriptionObserver
	{
	public:
		virtual ~EntitySubscriptionObserver() = default;
		virtual void onInsert(int entityId) = 0;
		virtual void onRemove(int entityId) = 0;
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

		std::vector<EntitySubscriptionObserver*> observers;

		const Aspect aspect;
	private:
		DynBitset dirtyEntityIds;
		DynBitset entityIds;
	};
}