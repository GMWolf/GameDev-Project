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
};

inline Material::Material()
{
}

inline Material::~Material()
{
}
