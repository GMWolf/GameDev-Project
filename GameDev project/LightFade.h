#pragma once
#include "Component.h"
COMPONENT(LightFade, 8, 3)
{
	LightFade() : fadeRate(0) {};
	LightFade(float rate) : fadeRate(rate) {};

	float fadeRate;
};
