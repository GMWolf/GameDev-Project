#pragma once
#include "AssetLoader.h"
#include "Assets.h"

class MaterialLoader : public AssetLoader
{
public:
	MaterialLoader(Assets& assets);
	~MaterialLoader();

	void load(std::string file, void* location) override;
private:
	Assets & assets;
};

