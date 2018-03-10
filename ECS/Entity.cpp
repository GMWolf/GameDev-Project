#include "Entity.h"
#include "Component.h"

Entity::Entity(int id) : id(id)
{
}

Entity Entity::create()
{
	const int id = entityManager.createEntity();
	return Entity(id);
}

Entity Entity::create(nlohmann::json json)
{
	Entity e = create();
	
	for (nlohmann::json::iterator it = json.begin(); it != json.end(); ++it) {
		baseComponentMapper* mapper = baseComponentMapper::mappersByName()->at(it.key());
		mapper->put(e.getId(), it.value());
		e.getAspect().set(mapper->getAspect());
		SubscriptionManager::bitTouched(e.getId(), mapper->getId());
	}

	return e;
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

Entity operator ""_entity(const char* s, std::size_t n)
{
	return Entity::create(nlohmann::json::parse(s, s + n));
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

