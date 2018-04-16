#pragma once
#include "System.h"
#include "EntitySubscription.h"
class LightFlickerSystem : public ECS::System
{
public:
	LightFlickerSystem();
	~LightFlickerSystem();

	void init();

	void update();

	void end();

private:
	ECS::EntitySubscription& entities;
};

