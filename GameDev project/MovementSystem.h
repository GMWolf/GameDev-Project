#pragma once
#include "Component.h"
#include "System.h"
#include "EntitySubscription.h"
#include "UISystem.h"
#include "PhysicsSystem.h"
#include "Assets.h"

COMPONENT(PlayerControl, 1)
{
};


class PlayerControlSystem : public ECS::System
{
public:

	PlayerControlSystem();

	~PlayerControlSystem() override;
	void init() override;
	void update() override;
	void end() override;

private:
	ECS::EntitySubscription & playerControled;
	UISystem* ui;
	PhysicsSystem* physics;

	Input* horizontal;
	Input* vertical;
	Input* upDown;
	Input* lookHorizontal;
	Input* lookVertical;
	Input* shoot;

	Assets& assets;

	bool SpaceReleased;
};