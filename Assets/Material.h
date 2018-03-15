#pragma once
#include "Texture.h"
#include "AssetHandle.h"

class Material
{
public:
	Material();
	~Material();

	AssetHandle<wagl::Texture> diffuse;
	AssetHandle<wagl::Texture> normal;
	AssetHandle<wagl::Texture> roughness;
};

