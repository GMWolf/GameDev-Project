#include "SubscriptionManager.h"

std::vector<EntitySubscription> SubscriptionManager::subscriptions(16);

std::map<Aspect, EntitySubscription*> SubscriptionManager::aspectSubscriptions;

std::vector<std::vector<EntitySubscription*>> SubscriptionManager::bitSubscriptions(32);


void SubscriptionManager::update()
{
	for (auto p : aspectSubscriptions) {
		p.second->update();
	}
}

void SubscriptionManager::bitTouched(int entityId, int bit)
{
	if (bitSubscriptions.size() > bit) {
		for (EntitySubscription* sub : bitSubscriptions[bit]) {
			sub->markDirty(entityId);
		}
	}
}

void SubscriptionManager::destroyed(int entityId, Aspect aspect)
{
	for (int i = 0; i < 32; i++) {
		if (aspect.has(i)) {
			if (bitSubscriptions.size() > i) {
				for (EntitySubscription* sub : bitSubscriptions[i]) {
					sub->markDirty(entityId);
					//TODO fix this!
				}
			}
		}
	}
}

EntitySubscription& SubscriptionManager::getSubscription(const Aspect aspect)
{
	EntitySubscription* subscription;

	if (aspectSubscriptions.find(aspect) == aspectSubscriptions.end()) {
		subscriptions.emplace_back(aspect);
		subscription = &subscriptions.back();
		aspectSubscriptions[aspect] = subscription;

		for (int i = 0; i < 32; i++) {
			if (aspect.has(i)) {
				if (bitSubscriptions.size() <= i) {
					bitSubscriptions.resize(i+1);
				}
				bitSubscriptions.at(i).push_back(subscription);
			}
		}
	}
	else {
		subscription = aspectSubscriptions[aspect];
	}

	return *subscription;
}