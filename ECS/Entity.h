#pragma once
#include <deque>
#include "Aspect.h"
#include "EntityManager.h"
#include "SubscriptionManager.h"
/*
** A Wrapper for an entity ID
** Lightweight so its ok to pass it around
** Adds convinient way to access components.
*/

class Entity
{
public:

	Entity(int id);

	static Entity Create();
	static void Destroy(Entity e);

	template<class T>
	T& get();

	template<class T>
	void add(T& component);

	template<class T, class... Args>
	void emplace(Args&& ... args);

	template<class T>
	void remove();

	template<class T>
	bool has();

	bool has(Aspect aspect);

	void clear();

	Aspect getAspect();

	bool operator==(const Entity& rhs) const;

	int getId() {
		return id;
	}

	Aspect & aspect;

	static EntityManager entityManager;
private:
	int id;

};



template<class T>
T& Entity::get()
{
	return T::componentMapper.get(id);
}

template<class T>
void Entity::add(T & component)
{
	T::componentMapper.put(id, component);
	aspect.set<T>();
	SubscriptionManager::bitTouched(id, T::componentId);
}

template<class T, class ...Args>
void Entity::emplace(Args && ... args)
{
	T::componentMapper.emplace(id, std::forward<Args> args...);
	aspect.set<T>();
	SubscriptionManager::bitTouched(id, T::componentId);
}

template<class T>
inline void Entity::remove()
{
	T::componentMapper.erase(id);
	aspect.unset<T>();
	SubscriptionManager::bitTouched(id, T::componentId);
}

template<class T>
inline bool Entity::has()
{
	return aspect.has<T>();
}
