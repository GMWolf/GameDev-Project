#pragma once
#include "Component.h"
#include "System.h"
#include "EntitySubscription.h"
#include "UISystem.h"
#include "PhysicsSystem.h"
#include "Assets.h"

COMPONENT(PlayerControl, 1)
{
	std::string horizontal;
	std::string vertical;
	float speed;

	void load(nlohmann::json& json)
	{
		horizontal = json["horizontal"].get<std::string>();
		vertical = json["vertical"].get<std::string>();

		speed = json["speed"];
	}
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

	bool SpaceReleased;
};