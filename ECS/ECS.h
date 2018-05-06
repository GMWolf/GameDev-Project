#pragma once
#include <string>
#include "json.hpp"
#include <map>
#include "Entity.h"
#include "ComponentLoader.h"

namespace ECS {


	struct LoadGroup
	{
		LoadGroup(LoadGroup* parent) : parent(parent)
		{
		}

		Entity getEntity(std::string tag)
		{
			if (tags.find(tag) != tags.end())
			{
				return tags[tag];
			}
			if (parent != nullptr)
			{
				return parent->getEntity(tag);
			}
			return Entity(-1);
		}

		void addEntity(std::string tag, Entity e)
		{
			tags.insert({tag, e});
		}
		std::map<std::string, Entity> tags;
		LoadGroup* parent;
	};

	LoadGroup& getLoadGroup();

	void loadScene(std::string fileName);

	void loadScene_json(nlohmann::json j);

	template<class T>
	inline void registerLoader(ComponentLoader* cl) {
		T::loader = cl;
	}
}