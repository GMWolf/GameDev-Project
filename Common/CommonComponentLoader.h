#pragma once
#include "ComponentLoader.h"
#include "json.hpp"

template<class T>
class CommonComponentLoader : public ComponentLoader
{
	void load(nlohmann::json& j, void* c) override
	{
		T* t = static_cast<T*>(c);
		t->load(j);
	}
};
