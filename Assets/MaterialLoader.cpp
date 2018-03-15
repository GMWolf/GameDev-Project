#include "stdafx.h"
#include "MaterialLoader.h"
#include "json.hpp"
#include "File.h"
#include "AssetManager.h"
#include "Assets.h"

void AssetLoader<Material>::load(std::string file, Material& mat)
{
	std::string str;
	File::read(file, str);
	nlohmann::json j = nlohmann::json::parse(str);

	mat.diffuse = assets.textures.get(j["diffuse"].get<std::string>());
	mat.normal = assets.textures.get(j["normal"].get<std::string>());
	mat.roughness = assets.textures.get(j["roughness"].get<std::string>());
}
