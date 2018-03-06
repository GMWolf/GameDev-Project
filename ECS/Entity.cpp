#include "Entity.h"
#include "Component.h"

Entity::Entity(int id) : id(id)
{
}

Entity Entity::create()
{
	int id = entityManager.createEntity();
	return Entity(id);
}

void Entity::destroy(Entity e)
{
	e.clear();
	entityManager.destroyEntity(e.id);
}

Aspect& Entity::getAspect() {
	return entityManager.aspects.at(id);
}

bool Entity::has(Aspect compare)
{
	return compare.subAspect(getAspect());
}

bool Entity::operator==(const Entity & rhs) const
{
	return id == rhs.id;
}

void Entity::clear() {
	for (int i = 0; i < ASPECT_SIZE; i++) {
		if (getAspect().has(i)) {
			baseComponentMapper::mappers()->at(i)->v_erase(id);
			getAspect().unset(i);
			SubscriptionManager::bitTouched(id, i);

		}
	}
}

EntityManager Entity::entityManager;

