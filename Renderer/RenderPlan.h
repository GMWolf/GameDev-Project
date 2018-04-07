#pragma once
#include <vector>
#include "AssetHandle.h"
#include "Material.h"
#include <glm/glm.hpp>
#include "Mesh.h"
#include <algorithm>
struct RenderObject
{
	glm::mat4 modelMatrix;
	AssetHandle<Mesh> mesh;
	AssetHandle<Material> material;
};

class RenderPlan
{
public:

	RenderPlan();
	~RenderPlan();

	std::vector<RenderObject> renderObjects;

	void optimize();

private:
	static bool compareRenderObjects(RenderObject& a, RenderObject& b);
};

