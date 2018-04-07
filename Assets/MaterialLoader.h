#pragma once
#include "Material.h"
#include <string>
#include "AssetManager.h"
#include "AssetLoader.h"
#include <Texture.h>

template<>
class AssetLoader<Material> {
public:

	explicit AssetLoader(AssetManager<wagl::Texture>& textures);
	
	void load(std::string file, Material& location) const;
private:
	AssetManager<wagl::Texture>& textures;
};