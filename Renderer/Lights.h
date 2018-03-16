#pragma once
#include <Component.h>
#include <Vector3.h>

COMPONENT(PointLight, 8)
{

	PointLight() : colour(1, 1, 1) , radius(1)
	{
	}

	PointLight(Vector3 colour, float power, float radius) : colour(colour), power(power), radius(radius)
	{
	}

	Vector3 colour;
	float radius;
	float power;
};