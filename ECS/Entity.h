#pragma once
#include <deque>
#include "Aspect.h"
#include "EntityManager.h"

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

	bool operator==(const Entity& rhs) const;

private:
	int id;

	static EntityManager entityManager;
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
	entityManager.aspects.at(id).set(T::componentMapper.componentId);
}

template<class T, class ...Args>
void Entity::emplace(Args && ... args)
{
	T::componentMapper.emplace(id, std::forward<Args> args...);
	entityManager.aspects.at(id).set(T::componentMapper.componentId);
}
