#include "stdafx.h"
#include "FontLoader.h"
#include <fstream>
#include <FontParser.h>

AssetLoader<Font>::AssetLoader(AssetManager<wagl::Texture>& textures) : textures(textures)
{
}

void AssetLoader<Font>::load(std::string file, Font& font) const
{
	std::ifstream is(file);

	parseFont(is, font.fontDescriptor);

	std::string texName = file.substr(0, file.find_last_of('.')) + ".png";;
	std::cout << "font texture " << texName << std::endl;
	font.texture = textures.get(file);
}
