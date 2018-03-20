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

COMPONENT(DirectionalLight, 1)
{
	
	DirectionalLight() : colour(1,1,1), power(1)
	{
	}

	DirectionalLight(Vector3 dir, Vector3 colour,float power) : dir(dir), colour(colour), power(power)
	{
	}

	Vector3 colour;
	Vector3 dir;
	float power;
};