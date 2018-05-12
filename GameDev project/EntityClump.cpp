#include "EntityClump.h"
#include "ECS.h"
#include "AssetsComponentLoader.h"
#include <glm/gtc/random.hpp>


EntityClumpSystem::EntityClumpSystem(Assets& assets): assets(assets)
{
}

void EntityClumpSystem::init()
{
	ECS::registerLoader<EntityClump>(new AssetsComponentLoader<EntityClump>(assets));
}

void EntityClumpSystem::update()
{
	while(!addedEntities.events.empty())
	{
		auto& e = addedEntities.events.front();

		Transform& t = e.entity.get<Transform>();
		EntityClump& c = e.entity.get<EntityClump>();

		
		int n = c.countMin;
		if (c.countMax > c.countMin) {
			n += (rand() % (c.countMax - c.countMin));
		}
		
		for(int i = 0; i < n; i++)
		{
			int r = rand() % c.prefabs.size();

			ECS::Entity s = ECS::Entity::create(assets.resolve(c.prefabs[r]));
			Transform& st = s.get<Transform>();
			st.position += glm::sphericalRand(1.0f) * c.area;
			st.rotation = glm::rotate(glm::mat4(1), (rand() / (float)RAND_MAX) * 2 * 3.1415f, glm::vec3(0, 1, 0));
			st.parent = e.entity;
		}

		addedEntities.events.pop();

	}
}

void EntityClumpSystem::end()
{
}
