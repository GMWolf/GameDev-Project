#pragma once
#include <string>
#include "Font.h"

template<>
class AssetLoader<Font> {
public:

	explicit AssetLoader(AssetManager<wagl::Texture>& textures);

	void load(std::string file, Font& location) const;
private:
	AssetManager<wagl::Texture>& textures;
};
