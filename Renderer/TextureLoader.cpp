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
	wagl::Texture* t = new (location) wagl::Texture(glTex);

	t->bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	return true;
}
