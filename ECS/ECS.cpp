#include "ECS.h"

void ECS::loadScene(std::string fileName)
{
	std::ifstream i(fileName);
	nlohmann::json j;
	i >> j;
	loadScene_json(j);
}

void ECS::loadScene_json(nlohmann::json j) {
	if (j.is_object()) {
		Entity::create(j);
	} else if (j.is_array()) {
		for (auto& jentity : j)
		{
			loadScene_json(jentity);
		}
	}
	else if (j.is_string()) {
		loadScene(j.get<std::string>());
	}
}
