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
	Velocity(Vector3 v) : v(v) {};

	Vector3 v;
};

class VelocitySystem : public System
{
public:

	VelocitySystem();

	void init() override;
	void update() override;
	void end() override;

private:
	EntitySubscription & velE;
};

