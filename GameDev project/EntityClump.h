#pragma once
#include "Component.h"
#include "AssetHandle.h"
#include "Prefab.h"
#include <glm/detail/type_vec3.hpp>
#include "Assets.h"
#include "System.h"
#include <EntityEvents.h>
#include <Transform.h>

COMPONENT(EntityClump, 8, 1)
{
	
	int countMin;
	int countMax;
	glm::vec3 area;
	std::vector<AssetHandle<ECS::Prefab>> prefabs;


	void load(const nlohmann::json& j, Assets& assets)
	{
		countMin = j["minimum count"];
		countMax = j["maximum count"];
		area.x = j["area"][0];
		area.y = j["area"][1];
		area.z = j["area"][2];

		for(const auto& a : j["prefabs"])
		{
			prefabs.push_back(assets.get<ECS::Prefab>(a.get<std::string>()));
		}
	}
};


class EntityClumpSystem : public ECS::System
{
public:
	EntityClumpSystem(Assets& assets);

	void init() override;
	void update() override;
	void end() override;

private:
	Assets & assets;
	ECS::EventQueue<ECS::EntityInserted<EntityClump, Transform>> addedEntities;
};