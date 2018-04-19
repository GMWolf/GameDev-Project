#include "Entity.h"
#include "Component.h"
namespace ECS {
	Entity::Entity() : id(-1)
	{
	}

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
			auto mappersByName = baseComponentMapper::mappersByName();
			if (mappersByName->find(it.key()) != mappersByName->end()) {
				baseComponentMapper* mapper = baseComponentMapper::mappersByName()->at(it.key());
				mapper->put(e.getId(), it.value());
				e.getAspect().set(mapper->getAspect());
				SubscriptionManager::bitTouched(e.getId(), mapper->getId());
			}
			else {
				std::cout << "could not find component " << it.key() << std::endl;
				for (auto& e : *mappersByName) {
					std::cout << e.first << std::endl;
				}
			}
			
		}

		return e;
	}

	Entity Entity::create(Prefab& prefab)
	{
		return create(prefab.json);
	}

	

	void Entity::destroy(Entity e)
	{
		e.clear();
		entityManager.destroyEntity(e.id);
	}

	Aspect& Entity::getAspect() {
		return entityManager.aspects.at(id);
	}

	const Aspect& Entity::getAspect() const
	{
		return entityManager.aspects.at(id);
	}

	bool Entity::has(Aspect compare) const
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

}