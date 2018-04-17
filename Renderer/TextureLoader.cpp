#include "stdafx.h"
#include "TextureLoader.h"
#include "Texture.h"
#include "SOIL.h"
#include <iostream>


TextureLoader::TextureLoader()
{
}


TextureLoader::~TextureLoader()
{
}

bool TextureLoader::load(std::string file, void* location)
{
	unsigned int flags = SOIL_FLAG_MIPMAPS;
	GLuint glTex = SOIL_load_OGL_texture(file.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, flags);
	if (glTex == 0)
	{
		std::cout << "Error loading texture " << file << std::endl;
		return false;
	}
	new (location) wagl::Texture(glTex);
	return true;
}
