#pragma once
#include <Component.h>
#include <glm/glm.hpp>
#include <ComponentLoader.h>

COMPONENT(PointLight, 8, 9)
{

	PointLight() : colour(1, 1, 1) , radius(1)
	{
	}

	PointLight(glm::vec3 colour, float power, float radius) : colour(colour), power(power), radius(radius)
	{
	}

	glm::vec3 colour;
	float radius;
	float power;
};

COMPONENT(DirectionalLight, 1, 10)
{
	
	DirectionalLight() : colour(1,1,1), power(1)
	{
	}

	DirectionalLight(glm::vec3 dir, glm::vec3 colour,float power) : dir(dir), colour(colour), power(power)
	{
	}

	glm::vec3 colour;
	glm::vec3 dir;
	float power;
};

class PointLightLoader : public ComponentLoader {
public:

	void load(nlohmann::json& j, void* c) override {
		PointLight* p = static_cast<PointLight*>(c);

		auto& colour = j["colour"];

		p->colour = glm::vec3(colour[0], colour[1], colour[2]);
		p->radius = j["radius"];
		p->power = j["power"];
	}

};