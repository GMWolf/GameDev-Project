#pragma once
#include <Component.h>
#include <glm/glm.hpp>

COMPONENT(PointLight, 8)
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

COMPONENT(DirectionalLight, 1)
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