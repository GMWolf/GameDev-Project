#pragma once
#include <Component.h>
#include <Vector3.h>

COMPONENT(PointLight, 8)
{

	PointLight() : colour(1, 1, 1) , radius(1)
	{
	}

	PointLight(Vector3 colour, float radius) : colour(colour), radius(radius)
	{
	}

	Vector3 colour;
	float radius;
};