#pragma once
#include "EntitySubscription.h"
#include "System.h"

class LightFadeSystem : public ECS::System
{
public:
	LightFadeSystem();
	~LightFadeSystem();

	void init() override;
	void update() override;
	void end() override;
private:
	ECS::EntitySubscription& entities;
};

