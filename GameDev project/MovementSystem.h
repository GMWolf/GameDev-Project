#pragma once
#include "Component.h"
#include "System.h"
#include "EntitySubscription.h"
#include "ApplicationAdapter.h"
#include "Vector2.h"
#include "UISystem.h"
#include "PhysicsSystem.h"
#include "Assets.h"

COMPONENT(PlayerControl, 1)
{
};


class PlayerControlSystem : public System
{
public:

	PlayerControlSystem(Assets& assets);

	~PlayerControlSystem() override;
	void init() override;
	void update() override;
	void end() override;

private:
	EntitySubscription & playerControled;
	UISystem* ui;
	PhysicsSystem* physics;

	Assets& assets;

	bool SpaceReleased;
};