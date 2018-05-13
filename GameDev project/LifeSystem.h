#pragma once
#include "Component.h"
#include "System.h"
#include "EntitySubscription.h"
#include "SubscriptionManager.h"
#include "Entity.h"
#include "DeltaTime.h"
COMPONENT(Life, 8)
{
	float t;

	void load(const nlohmann::json& j)
	{
		t = j["time"];
	}
};


class LifeSystem : public ECS::System
{
public:
	LifeSystem();

	void init() override;

	void update() override;

	void end() override;

private:
	ECS::EntitySubscription& entities;
};