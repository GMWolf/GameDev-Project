#pragma once
#include "AssetHandle.h"
#include <Texture.h>

class Material
{
public:
	Material();
	~Material();

	AssetHandle<wagl::Texture> diffuse;
	AssetHandle<wagl::Texture> normal;
	AssetHandle<wagl::Texture> roughness;
	AssetHandle<wagl::Texture> alpha;

	bool useAlpha;
};

inline Material::Material()
{
}

inline Material::~Material()
{
}
