#pragma once
#include "Component.h"
#include "System.h"
#include "EntitySubscription.h"
#include "PhysicsSystem.h"

COMPONENT(Bullet, 16)
{
	volatile float damage;

	void load(const nlohmann::json& j)
	{
		damage = j["damage"];
	}
};

class BulletSystem : public ECS::System
{
public:
	BulletSystem();
	~BulletSystem();
	void init() override;
	void update() override;
	void end() override;
private:
	ECS::EntitySubscription& bullets;
	PhysicsSystem* physics;
};

