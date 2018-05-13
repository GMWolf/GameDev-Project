#pragma once
#include "Component.h"
COMPONENT(Gun, 1)
{
	
	Gun(): fireRate(0), coolDown(0){} ;
	Gun(float fireRate) : fireRate(fireRate), coolDown(0) {};

	float fireRate;
	float coolDown;
	float velocity;
	AssetHandle<ECS::Prefab> projectile;

	void load(const nlohmann::json& j, Assets& assets)
	{
		fireRate = j["fireRate"].get<int>();
		projectile = assets.get<ECS::Prefab>(j["projectile"].get<std::string>());
		velocity = j["velocity"];
	}
};