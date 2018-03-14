#pragma once
#include <Texture.h>
#include <string>
class ImageLoader
{
public:
	static wagl::Texture* Load(std::string file, bool mipmap = true, bool compress = false);

private:
	ImageLoader();
	~ImageLoader();
};

