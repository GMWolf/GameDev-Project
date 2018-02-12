#include "Texture.h"



Texture::Texture(std::string file, bool mipmap, bool compress)
{
	unsigned int flags = 0;
	if (mipmap) {
		flags |= SOIL_FLAG_MIPMAPS;
	}

	if (compress) {
		flags |= SOIL_FLAG_COMPRESS_TO_DXT;
	}

	SOIL_load_OGL_texture(file.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, flags);
}

Texture::~Texture()
{
	glDeleteTextures(1, &glTex);
}
