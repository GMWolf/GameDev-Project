#pragma once
#include "System.h"
#include "EntitySubscription.h"
#include "Assets.h"

class ParticleSystem : public ECS::System
{
public:
	ParticleSystem(Assets& assets);
	~ParticleSystem();
	void init() override;
	void update() override;
	void end() override;

private:
	ECS::EntitySubscription& particles;
	ECS::EntitySubscription& spawners;

	Assets& assets;
};

