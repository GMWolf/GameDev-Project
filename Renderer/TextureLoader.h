#pragma once
#include "AssetLoader.h"

class TextureLoader : public AssetLoader
{
public:
	TextureLoader();
	~TextureLoader();
	void load(std::string file, void* location) override;
};

