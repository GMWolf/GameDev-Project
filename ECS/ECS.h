#pragma once
#include <string>
#include "json.hpp"
#include <fstream>
#include "Entity.h"
#include "ComponentLoader.h"

namespace ECS {

	inline void loadScene(std::string fileName)
	{

		std::ifstream i(fileName);
		nlohmann::json j;
		i >> j;

		for (auto& jentity : j)
		{
			if (jentity.is_string())
			{
				loadScene(jentity.get<std::string>());
			}
			else {
				Entity::create(jentity);
			}
		}
	}

	template<class T>
	inline void registerLoader(ComponentLoader* cl) {
		T::loader = cl;
	}
}