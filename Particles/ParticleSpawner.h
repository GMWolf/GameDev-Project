#pragma once
#include "Component.h"
#include "Prefab.h"
#include "AssetHandle.h"
#include <glm/detail/type_vec3.hpp>
#include "Assets.h"
COMPONENT(ParticleSpawner, 8)
{
	float rate;
	float carry = 0;

	AssetHandle<ECS::Prefab> prefab;

	glm::vec3 area;
	glm::vec3 velocity;
	glm::vec3 gravity;

	float life;
	void load(const nlohmann::json& j, Assets& assets)
	{
		area.x = j["area"][0];
		area.y = j["area"][1];
		area.z = j["area"][2];

		velocity.x = j["velocity"][0];
		velocity.y = j["velocity"][1];
		velocity.z = j["velocity"][2];

		gravity.x = j["gravity"][0];
		gravity.y = j["gravity"][1];
		gravity.z = j["gravity"][2];

		prefab = assets.get<ECS::Prefab>(j["prefab"]);

		life = j["life"];
		rate = j["rate"];
	}
};
