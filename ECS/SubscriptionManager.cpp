#include "SubscriptionManager.h"

std::vector<EntitySubscription> SubscriptionManager::subscriptions;

std::map<Aspect, EntitySubscription*> SubscriptionManager::aspectSubscriptions;

std::vector<std::vector<EntitySubscription*>> SubscriptionManager::bitSubscriptions(ASPECT_SIZE);


void SubscriptionManager::update()
{
	for (EntitySubscription& s : subscriptions) {
		s.update();
	}
	/*for (auto p : aspectSubscriptions) {
		p.second->update();
	}*/
}

void SubscriptionManager::bitTouched(int entityId, int bit)
{
	if (bitSubscriptions.size() > bit) {
		for (EntitySubscription* sub : bitSubscriptions[bit]) {
			sub->markDirty(entityId);
		}
	}
	/*for (EntitySubscription& es : subscriptions) {
		if (es.aspect.bits & bit) {
			es.markDirty(entityId);
		}
	}*/
}

EntitySubscription& SubscriptionManager::getSubscription(const Aspect aspect)
{
	EntitySubscription* subscription;

	if (aspectSubscriptions.find(aspect) == aspectSubscriptions.end()) {
		subscriptions.emplace_back(aspect);
		subscription = &(subscriptions.back());
		aspectSubscriptions[aspect] = subscription;

		for (int i = 0; i < ASPECT_SIZE; i++) {
			if (aspect.has(i)) {
				bitSubscriptions[i].push_back(subscription);
			}
		}
	}
	else {
		subscription = aspectSubscriptions[aspect];
	}

	return *subscription;
}