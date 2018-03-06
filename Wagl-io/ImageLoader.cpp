#include "stdafx.h"
#include "ImageLoader.h"
#include <SOIL.h>

Texture * ImageLoader::Load(std::string file, bool mipmap, bool compress)
{
	unsigned int flags = 0;
	if (mipmap) {
		flags |= SOIL_FLAG_MIPMAPS;
	}

	if (compress) {
		flags |= SOIL_FLAG_COMPRESS_TO_DXT;
	}

	GLint glTex = SOIL_load_OGL_texture(file.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, flags);
	return new Texture(glTex);
}

ImageLoader::ImageLoader()
{
}


ImageLoader::~ImageLoader()
{
}
