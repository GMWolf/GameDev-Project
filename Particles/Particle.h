#pragma once
#include "Component.h"
#include <glm/detail/type_vec3.hpp>

COMPONENT(Particle, 64)
{
	glm::vec3 velocity;
	glm::vec3 gravity;

	float life;

	void load(const nlohmann::json& j)
	{

	}
};
