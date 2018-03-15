#include "stdafx.h"
#include "TextureLoader.h"
#include "AssetLoader.h"
#include <SOIL.h>
#include <iostream>

void AssetLoader<wagl::Texture>::load(std::string file, wagl::Texture& texture)
{
	unsigned int flags = SOIL_FLAG_MIPMAPS;
	GLuint glTex = SOIL_load_OGL_texture(file.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, flags);
	std::cout << "tex " << (int)glTex << std::endl;
	texture.glTex = glTex;
}
