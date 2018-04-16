#include "stdafx.h"
#include "MaterialLoader.h"
#include "Material.h"
#include "json.hpp"
#include <fstream>


MaterialLoader::MaterialLoader(Assets& assets) : assets(assets)
{
}


MaterialLoader::~MaterialLoader()
{
}

void MaterialLoader::load(std::string file, void* location)
{

	Material* mat = new (location) Material;

	std::ifstream i(file);
	nlohmann::json j;
	i >> j;

	mat->diffuse = assets.get<wagl::Texture>(j["diffuse"].get<std::string>());
	mat->normal = assets.get<wagl::Texture>(j["normal"].get<std::string>());
	mat->roughness = assets.get<wagl::Texture>(j["roughness"].get<std::string>());
}
