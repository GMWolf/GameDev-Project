#pragma once
#include "LinearMath/btMotionState.h"
#include "Entity.h"

class EntityMotionState : public btMotionState
{
public:
	EntityMotionState(const ECS::Entity& e);
	~EntityMotionState();
	void getWorldTransform(btTransform& worldTrans) const override;
	void setWorldTransform(const btTransform& worldTrans) override;

private:
	ECS::Entity entity;
};

