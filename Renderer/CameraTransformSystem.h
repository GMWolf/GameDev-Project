#pragma once
#include "System.h"
#include "EntitySubscription.h"

class CameraTransformSystem : public ECS::System
{
public:
	CameraTransformSystem();
	~CameraTransformSystem();


	void init() override;
	void update() override;
	void end() override;


	ECS::EntitySubscription& cameras;
};

