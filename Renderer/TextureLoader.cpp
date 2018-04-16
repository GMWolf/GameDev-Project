#include "stdafx.h"
#include "TextureLoader.h"
#include "Texture.h"
#include "SOIL.h"


TextureLoader::TextureLoader()
{
}


TextureLoader::~TextureLoader()
{
}

void TextureLoader::load(std::string file, void* location)
{
	unsigned int flags = SOIL_FLAG_MIPMAPS;
	GLuint glTex = SOIL_load_OGL_texture(file.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, flags);
	new (location) wagl::Texture(glTex);
}
