#include "stdafx.h"
#include "MaterialLoader.h"
#include "json.hpp"
#include "File.h"
#include "AssetManager.h"
#include "Assets.h"

AssetLoader<Material>::AssetLoader(AssetManager<wagl::Texture>& textures) : textures(textures)
{
}

void AssetLoader<Material>::load(std::string file, Material & mat)
{

	std::string str;
	File::read(file, str);
	nlohmann::json j = nlohmann::json::parse(str);

	mat.diffuse = textures.get(j["diffuse"].get<std::string>());
	mat.normal = textures.get(j["normal"].get<std::string>());
	mat.roughness = textures.get(j["roughness"].get<std::string>());
}
