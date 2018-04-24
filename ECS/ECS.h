#pragma once
#include <string>
#include "json.hpp"
#include <fstream>
#include "Entity.h"
#include "ComponentLoader.h"

namespace ECS {

	void loadScene(std::string fileName);

	void loadScene_json(nlohmann::json j);

	template<class T>
	inline void registerLoader(ComponentLoader* cl) {
		T::loader = cl;
	}
}