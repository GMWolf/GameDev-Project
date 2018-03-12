#pragma once
#include "Event.h"
#include "Entity.h"
#include "EntitySubscription.h"
template<class... components>
struct EntityInserted : Event<EntityInserted<components...>>
{
	EntityInserted(Entity entity) : entity(entity)
	{
	}

	Entity entity;
};

template<class... components>
struct EntityRemoved : Event<EntityInserted<components...>>
{
	EntityRemoved(Entity entity) : entity(entity)
	{
	}

	Entity entity;
};


//specialization for inserted
template<class... components>
class EventQueue<EntityInserted<components...>> : public EntitySubscriptionObserver{
public:
	EventQueue()
	{
		SubscriptionManager::getSubscription(Aspect::getAspect<components...>()).observers.push_back(this);
	}

	~EventQueue()
	{
		auto& observers = SubscriptionManager::getSubscription(Aspect::getAspect<components...>()).observers;
		auto t = std::find(observers.begin(), observers.end(), this);
		observers.erase(t);
	}

	void onInsert(int entityId) override
	{
		events.emplace(entityId);
	}
	void onRemove(int entityId) override
	{
	}

	std::queue<EntityInserted<components...>> events;
};

template<class... components>
class EventQueue<EntityRemoved<components...>> : public EntitySubscriptionObserver {
public:
	EventQueue()
	{
		SubscriptionManager::getSubscription(Aspect::getAspect<components...>()).observers.push_back(this);
	}

	~EventQueue()
	{
		auto& observers = SubscriptionManager::getSubscription(Aspect::getAspect<components...>()).observers;
		auto t = std::find(observers.begin(), observers.end(), this);
		observers.erase(t);
	}

	void onInsert(int entityId) override
	{
	}
	void onRemove(int entityId) override
	{
		events.emplace(entityId);
	}

	std::queue<EntityInserted<components...>> events;
};


