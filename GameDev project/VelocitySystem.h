#pragma once
#include "Component.h"
#include "Vector3.h"
#include "System.h"
#include "EntitySubscription.h"
#include "SubscriptionManager.h"
#include "Transform.h"
#include "DeltaTime.h"

COMPONENT(Velocity, 16)
{
	Velocity() : v(0,0,0) {};
	Velocity(glm::vec3 v) : v(v) {};

	glm::vec3 v;

	void load(const nlohmann::json& j)
	{
		v.x = j["velocity"][0];
		v.y = j["velocity"][1];
		v.z = j["velocity"][2];
	}
};

class VelocitySystem : public ECS::System
{
public:

	VelocitySystem();

	void init() override;
	void update() override;
	void end() override;

private:
	ECS::EntitySubscription & velE;
};

