#pragma once
#include "Component.h"
#include "System.h"
#include "EntitySubscription.h"
#include "ApplicationAdapter.h"
#include "Vector2.h"
#include "UISystem.h"

COMPONENT(PlayerControl, 1)
{
};


class PlayerControlSystem : public System
{
public:

	PlayerControlSystem();

	~PlayerControlSystem() override;
	void init() override;
	void update() override;
	void end() override;

private:
	EntitySubscription & playerControled;
	UISystem* ui;

	bool SpaceReleased;
};