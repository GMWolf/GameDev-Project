#pragma once
#include <Component.h>

COMPONENT(lightFlicker, 8, 4) {

	lightFlicker() {
	}

	lightFlicker(float min, float max, float rate, float off) : min(min), max(max), rate(rate), off(off) {
	}

	float min;
	float max;

	float rate;
	float off;

};