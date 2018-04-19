#pragma once
#include "AssetLoader.h"
#include <json.hpp>
#include <fstream>
#include <iostream>
#include <Prefab.h>
class PrefabLoader : public AssetLoader
{
public:
	bool load(std::string file, void* location) {
		std::ifstream i(file);
		if (!i.is_open())
		{
			std::cout << "Error opening file " << file << std::endl;
			return false;
		}

		ECS::Prefab* j = new (location) ECS::Prefab;

		i >> j->json;
	}
};

