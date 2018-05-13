#pragma once
#include "Component.h"
COMPONENT(Gun, 1)
{
	
	Gun(): fireRate(0), coolDown(0){} ;
	Gun(float fireRate) : fireRate(fireRate), coolDown(0) {};

	float fireRate;
	float coolDown;

	void load(const nlohmann::json& j)
	{
		fireRate = j["fireRate"].get<int>();
	}
};