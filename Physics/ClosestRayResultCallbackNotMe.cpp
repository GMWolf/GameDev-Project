#include "ClosestRayResultCallbackNotMe.h"



ClosestRayResultCallbackNotMe::ClosestRayResultCallbackNotMe(btVector3 start, btVector3 end, int userIndex): ClosestRayResultCallback(start, end), userIndex(userIndex)
{
}


ClosestRayResultCallbackNotMe::~ClosestRayResultCallbackNotMe()
{
}
