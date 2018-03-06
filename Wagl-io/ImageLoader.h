#pragma once
#include <Texture.h>
#include <string>
class ImageLoader
{
public:
	static Texture* Load(std::string file, bool mipmap = true, bool compress = false);

private:
	ImageLoader();
	~ImageLoader();
};

