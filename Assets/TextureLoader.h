#pragma once
#include <Texture.h>
#include <string>
#include <Texture.h>
#include "AssetLoader.h"


template<>
class AssetLoader<wagl::Texture> {
public:
	void load(std::string file, wagl::Texture& location);
};