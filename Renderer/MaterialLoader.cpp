#include "stdafx.h"
#include "MaterialLoader.h"
#include "Material.h"
#include "json.hpp"
#include <fstream>
#include <iostream>


MaterialLoader::MaterialLoader(Assets& assets) : assets(assets)
{
}


MaterialLoader::~MaterialLoader()
{
}

bool MaterialLoader::load(std::string file, void* location)
{

	Material* mat = new (location) Material;

	std::ifstream i(file);

	if (!i.is_open())
	{
		std::cout << "Error opening file " << file << std::endl;
		return false;
	}

	nlohmann::json j;
	i >> j;

	mat->diffuse = assets.get<wagl::Texture>(j["diffuse"].get<std::string>());
	mat->normal = assets.get<wagl::Texture>(j["normal"].get<std::string>());
	mat->roughness = assets.get<wagl::Texture>(j["roughness"].get<std::string>());

	if (j.find("alpha") != j.end())
	{
		mat->alpha = assets.get<wagl::Texture>(j["alpha"].get<std::string>());
		mat->useAlpha = true;
	} else
	{
		mat->useAlpha = false;
	}

	if (j.find("emit") != j.end())
	{
		mat->emit.x = j["emit"][0];
		mat->emit.y = j["emit"][1];
		mat->emit.z = j["emit"][2];
	} else
	{
		mat->emit = glm::vec3(0, 0, 0);
	}

	return true;
}
