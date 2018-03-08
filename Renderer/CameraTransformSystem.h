#pragma once
#include "System.h"
#include "EntitySubscription.h"

class CameraTransformSystem : public System
{
public:
	CameraTransformSystem();
	~CameraTransformSystem();


	void init() override;
	void update() override;
	void end() override;


	EntitySubscription& cameras;
};

