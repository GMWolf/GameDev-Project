#include "Entity.h"

Entity::Entity(int id) : id(id)
{
}

Entity Entity::Create()
{
	int id = getNewId();
	aspects.put(id, Aspect());
	return Entity(id);
}

void Entity::Destroy(Entity e)
{
	aspects.erase(e.id);
	ids.push_back(e.id);
}

inline int Entity::getNewId() {
	if (ids.empty()) {
		int _id = ids.front();
		ids.pop_front();
		return _id;
	}

	return nextID++;
}
