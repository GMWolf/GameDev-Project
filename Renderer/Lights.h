#pragma once
#include <Component.h>

COMPONENT(PointLight, 8)
{

	PointLight() : intensity(1)
	{
	}

	PointLight(const float intensity) : intensity(intensity)
	{
	}

	float intensity;
};