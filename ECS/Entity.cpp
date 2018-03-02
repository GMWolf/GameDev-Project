#include "Entity.h"

Entity::Entity(int id) : id(id)
{
}

Entity Entity::Create()
{
	int id = entityManager.createEntity();
	return Entity(id);
}

void Entity::Destroy(Entity e)
{
	entityManager.destroyEntity(e.id);
}

bool Entity::operator==(const Entity & rhs) const
{
	return id == rhs.id;
}

EntityManager Entity::entityManager;

