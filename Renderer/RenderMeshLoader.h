#pragma once
#include "AssetLoader.h"
#include "Assets.h"

class RenderMeshLoader : public AssetLoader
{
public:
	RenderMeshLoader(Assets& assets);
	~RenderMeshLoader();
	bool load(std::string file, void* location) override;

private:
	Assets & assets;
};

