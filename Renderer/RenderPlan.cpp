#include "stdafx.h"
#include "RenderPlan.h"


RenderPlan::RenderPlan()
{
}


RenderPlan::~RenderPlan()
{
}

void RenderPlan::optimize()
{
	//Sort items with material first, mesh second.
	std::sort(renderObjects.begin(), renderObjects.end(), compareRenderObjects);
}

bool RenderPlan::compareRenderObjects(RenderObject& a, RenderObject& b)
{
	if (a.material.assetId == b.material.assetId)
	{
		return a.mesh.assetId < b.mesh.assetId;
	}
	else
	{
		return a.material.assetId < b.material.assetId;
	}
}
