#pragma once
#include "BulletCollision/CollisionDispatch/btCollisionWorld.h"

class ClosestRayResultCallbackNotMe : public btCollisionWorld::ClosestRayResultCallback
{
public:
	ClosestRayResultCallbackNotMe(btVector3 start, btVector3 end, int userIndex);
	~ClosestRayResultCallbackNotMe();


	btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool normalInWorldSpace) override
	{
		if (rayResult.m_collisionObject->getUserIndex() != userIndex)
		{
			return ClosestRayResultCallback::addSingleResult(rayResult, normalInWorldSpace);
		}
		return m_closestHitFraction;
	}

private:
	int userIndex;
};

