#pragma once
#include <string>

class AssetLoader {
public:
	virtual ~AssetLoader() = default;
	virtual void load(std::string file, void* location) = 0;
};