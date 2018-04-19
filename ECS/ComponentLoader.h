#pragma once
class ComponentLoader {
public:
	virtual void load(nlohmann::json& j, void* c) = 0;

};