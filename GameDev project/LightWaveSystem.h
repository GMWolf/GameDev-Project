#pragma once
#include "System.h"
#include "EntitySubscription.h"
class LightWaveSystem : public System
{
public:
	LightWaveSystem();
	~LightWaveSystem();

	void init();

	void update();

	void end();

private:
	EntitySubscription& entities;
};

