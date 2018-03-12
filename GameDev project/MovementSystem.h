#pragma once
#include "Component.h"
#include "System.h"
#include "EntitySubscription.h"
#include "ApplicationAdapter.h"
#include "Vector2.h"

COMPONENT(PlayerControl, 1)
{
};


class PlayerControlSystem : public System
{
public:

	PlayerControlSystem(GLFWwindow* window);

	~PlayerControlSystem() override;
	void init() override;
	void update() override;
	void end() override;

private:
	EntitySubscription & playerControled;
	GLFWwindow* window;
	Vector2 mousePrevious;

	bool SpaceReleased;
};