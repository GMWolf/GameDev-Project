#pragma once
#include "EntitySubscription.h"

class SubscriptionManager
{
public:

	static void update();

	static void bitTouched(int entityId, unsigned bit);


	static EntitySubscription& getSubscription(const Aspect aspect);

	//Subscription store
	static std::vector<EntitySubscription*> subscriptions;

	//used to get subscription
	static std::map<Aspect, EntitySubscription*> aspectSubscriptions;

	//Used to alert subscriptions
	static std::vector<std::vector<EntitySubscription*>> bitSubscriptions; //componentbit -> list of subscriptions
};