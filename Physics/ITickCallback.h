#pragma once
#include "LinearMath/btScalar.h"

class ITickCallback
{
public:
	virtual ~ITickCallback() = default;

	virtual void tickCallback(btScalar timestep) = 0;

	virtual void pretickCallback(btScalar timestep) = 0;
};
