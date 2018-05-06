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
	float maxChange;
	float maxForce;

	void load(nlohmann::json& json)
	{
		horizontal = json["horizontal"].get<std::string>();
		vertical = json["vertical"].get<std::string>();

		speed = json["speed"];
		maxChange = json["maxChange"];
		maxForce = json["maxForce"];
	}
};


class PlayerControlSystem : public ECS::System, public ITickCallback
{
public:

	PlayerControlSystem();

	~PlayerControlSystem() override;
	void init() override;
	void update() override;
	void end() override;

	void tickCallback(btScalar timestep) override;
	void pretickCallback(btScalar timestep) override;
private:
	ECS::EntitySubscription & playerControled;
	UISystem* ui;
	PhysicsSystem* physics;

};