#pragma once
#include "AssetHandle.h"
#include <Texture.h>
#include <glm/detail/type_vec3.hpp>

class Material
{
public:
	Material();
	~Material();

	AssetHandle<wagl::Texture> diffuse;
	AssetHandle<wagl::Texture> normal;
	AssetHandle<wagl::Texture> roughness;
	AssetHandle<wagl::Texture> alpha;
	glm::vec3 emit;
	bool useAlpha;
};

inline Material::Material()
{
}

inline Material::~Material()
{
}
