#pragma once
#include "System.h"
#include "EntitySubscription.h"
class LightFlickerSystem : public System
{
public:
	LightFlickerSystem();
	~LightFlickerSystem();

	void init();

	void update();

	void end();

private:
	EntitySubscription& entities;
};

