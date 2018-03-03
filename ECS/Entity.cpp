#include "Entity.h"
#include "Component.h"

Entity::Entity(int id) : id(id), aspect(entityManager.aspects.at(id))
{
}

Entity Entity::Create()
{
	int id = entityManager.createEntity();
	return Entity(id);
}

void Entity::Destroy(Entity e)
{
	e.clear();
	entityManager.destroyEntity(e.id);
}

bool Entity::has(Aspect compare)
{
	return compare.subAspect(aspect);
}

bool Entity::operator==(const Entity & rhs) const
{
	return id == rhs.id;
}

void Entity::clear() {
	for (int i = 0; i < ASPECT_SIZE; i++) {
		if (aspect.has(i)) {
			baseComponentMapper::mappers()->at(i)->v_erase(id);
			aspect.unset(i);
			SubscriptionManager::bitTouched(id, i);
		}
	}
}

EntityManager Entity::entityManager;

