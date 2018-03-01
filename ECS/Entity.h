#pragma once
#include <deque>
#include <HashedArrayTree.h>
#include "Aspect.h"
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

private:
	int id;

	static int getNewId();
	static int nextID;
	static std::deque<int> ids;
	static HashedArrayTree<32, Aspect> aspects;
};

template<class T>
T& Entity::get()
{
	return T::mapper.get<id>();
}

template<class T>
void Entity::add(T & component)
{
	T::mapper.put(id, component);
	aspects.at(id).set(T::componentId);
}
