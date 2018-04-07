#pragma once
#include "AssetLoader.h"
#include "RenderMesh.h"
#include "AssetManager.h"

template<>
class AssetLoader<RenderMesh>
{
public:

	explicit AssetLoader(AssetManager<Mesh>& meshes);

	void load(std::string file, RenderMesh& location) const;

private:

	AssetManager<Mesh>& meshes;
};

