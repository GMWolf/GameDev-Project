#pragma once
#include <Component.h>
#include <Transform.h>
#include <System.h>
#include <EntitySubscription.h>
#include <SubscriptionManager.h>

COMPONENT(Rotate, 16, 6)
{

	Rotate(): rate(0)
	{
	}
	Rotate(float rate) : rate(rate)
	{
	}

	void load(const nlohmann::json& j)
	{
		rate = j["rate"].get<float>();
	}

	float rate;
};

class RotateSystem : public ECS::System
{
public:
	RotateSystem();
	~RotateSystem();

	void init() override;
	void update() override;
	void end() override;

	ECS::EntitySubscription& entities;

};

