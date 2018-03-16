#pragma once
#include <Component.h>

COMPONENT(lightWave, 8) {

	lightWave() {
	}

	lightWave(float min, float max, float rate, float off) : min(min), max(max), rate(rate), off(off) {
	}

	float min;
	float max;

	float rate;
	float off;

};