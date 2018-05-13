#pragma once
#include "Component.h"
#include "System.h"
#include "EntitySubscription.h"

COMPONENT(AlignToVelocity, 16)
{
	bool align;

	void load(const nlohmann::json& j)
	{
		align = true;
	}
};

class AlignVelocitySystem : public ECS::System
{
public:
	AlignVelocitySystem();
	~AlignVelocitySystem();

	void init() override;
	void update() override;
	void end() override;
private:
	ECS::EntitySubscription& entities;
};

