#pragma once
#include <string>

class AssetLoader {
public:
	virtual ~AssetLoader() = default;
	virtual bool load(std::string file, void* location) = 0;
};