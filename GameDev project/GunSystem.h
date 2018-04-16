#pragma once
#include "System.h"
#include "EntitySubscription.h"
#include "UISystem.h"
#include "PhysicsSystem.h"
#include "Assets.h"

class GunSystem : public ECS::System
{
public:
	GunSystem(Assets& assets);
	~GunSystem();

	void init() override;
	void update() override;
	void end() override;
private:
	Assets & assets;

	ECS::EntitySubscription & entities;

	UISystem* ui;
	PhysicsSystem* physics;

	Input* shoot;
};

