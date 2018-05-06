#include "ECS.h"
#include <fstream>
#include <iostream>

ECS::LoadGroup* currentLoadGroup = nullptr;

ECS::LoadGroup& ECS::getLoadGroup()
{
	return *currentLoadGroup;
}

void ECS::loadScene(std::string fileName)
{
	std::ifstream i(fileName);
	nlohmann::json j;
	i >> j;
	loadScene_json(j);
}

void ECS::loadScene_json(nlohmann::json j) {
	

	if (j.is_object()) {
		Entity e = Entity::create(j);
		//Add to group if has a tag
		if (j.find("tag") != j.end())
		{
			currentLoadGroup->addEntity(j["tag"], e);
			std::cout << "adding " << j["tag"] << std::endl;
		}
	}
	else {
		LoadGroup lg(currentLoadGroup);
		currentLoadGroup = &lg;
		if (j.is_array()) {
			for (auto& jentity : j)
			{
				loadScene_json(jentity);
			}
		}
		else if (j.is_string()) {
			loadScene(j.get<std::string>());
		}

		currentLoadGroup = lg.parent;
	}

}
