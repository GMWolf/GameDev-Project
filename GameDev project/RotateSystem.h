#pragma once
#include <Component.h>
#include <Transform.h>
#include <System.h>
#include <EntitySubscription.h>
#include <SubscriptionManager.h>

COMPONENT(Rotate, 16)
{

	Rotate(): rate(0)
	{
	}
	Rotate(float rate) : rate(rate)
	{
	}

	float rate;
};

class RotateSystem : public System
{
public:
	RotateSystem();
	~RotateSystem();

	void init() override;
	void update() override;
	void end() override;

	EntitySubscription& entities;

};

